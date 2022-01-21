//
// Copyright (C) 2018 Dr. Michael Steffens
//
// SPDX-License-Identifier:     BSL-1.0
//


#include <charconv>
#include <cstddef>
#include <csv.hpp>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string_view>

std::list<std::size_t> fieldSelection(std::string_view const& fieldSelectionStr)
{
	std::list<std::size_t> result;
	csv::CSVReader rows{csv::parse(fieldSelectionStr, csv::CSVFormat().no_header().quote(false))};
	for (csv::CSVRow& row : rows) {
		for (csv::CSVField& field : row) {
			std::string_view selectionStr{field.get<std::string_view>()};
			std::size_t selection;
			if (std::from_chars(selectionStr.data(), selectionStr.data() + selectionStr.length(), selection).ec != std::errc()) {
				throw(std::runtime_error("Failed to parse field selection"));
			}
			result.push_back(selection);
		}
	}
	return result;
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		throw(std::runtime_error("Usage: cutcsv <field-selection>"));
	}
	std::list<std::size_t> fieldIndices{fieldSelection(argv[1])};
	csv::CSVFormat format;
	format.no_header().quote(true);
	csv::CSVReader reader{std::cin, format};
	csv::DelimWriter writer{csv::make_csv_writer(std::cout)};
	for (csv::CSVRow& row : reader) {
	  std::list<std::string_view> fieldViews;
	  for (std::size_t fieldIndex : fieldIndices) {
	    fieldViews.emplace_back(row[fieldIndex].get<std::string_view>());
	  }
	  writer << fieldViews;
	}
	return 0;
}
