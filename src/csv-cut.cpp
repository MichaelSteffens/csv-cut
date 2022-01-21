//
// Copyright (C) 2022 Dr. Michael Steffens
//
// SPDX-License-Identifier:     BSL-1.0
//


#include <charconv>
#include <cstddef>
#include <csv.hpp>
#include <cxxopts/cxxopts.hpp>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
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
	cxxopts::Options options("csv_cut", "Cut fields from CSV input");

	options.add_options()("h,help", "Print usage")("d,delimiter", "Input delimiter", cxxopts::value<char>()->default_value(","))(
		"f,fields", "Comma separated list of fields", cxxopts::value<std::string>()->default_value(""));

	cxxopts::ParseResult option{options.parse(argc, argv)};
	if (option.count("help")) {
		std::cout << options.help() << std::endl;
		exit(0);
	}

	char delimiter{option["delimiter"].as<char>()};

	std::list<std::size_t> fieldIndices{fieldSelection(option["fields"].as<std::string>())};
	csv::CSVReader reader{std::cin, csv::CSVFormat().no_header().quote(true).delimiter(delimiter)};
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