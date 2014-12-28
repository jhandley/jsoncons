// Copyright 2013 Daniel Parker
// Distributed under Boost license

#include <boost/test/unit_test.hpp>
#include "jsoncons/json.hpp"
#include "jsoncons/json_serializer.hpp"
#include "jsoncons/json_reader.hpp"
#include <sstream>
#include <vector>
#include <utility>
#include <ctime>

using jsoncons::parsing_context;
using jsoncons::json_deserializer;
using jsoncons::json;
using jsoncons::wjson;
using jsoncons::json_reader;
using jsoncons::json_input_handler;
using jsoncons::input_error_handler;
using jsoncons::json_parse_exception;
using jsoncons::json_parser_category;
using jsoncons::input_error_handler;
using jsoncons::default_input_error_handler;
using std::string;

class my_input_error_handler : public input_error_handler
{
private:
    virtual void do_warning(std::error_code ec,
                            parsing_context context) throw(json_parse_exception)
    {
    }

    virtual void do_error(std::error_code ec,
                          parsing_context context) throw(json_parse_exception)
    {
		if (ec.value() != jsoncons::json_parser_error::unexpected_trailing_value_separator)
		{
			default_input_error_handler::instance().error(ec,context);
		}
    }
};

BOOST_AUTO_TEST_CASE(test_accept_trailing_value_separator)
{
    my_input_error_handler err_handler;

    json val = json::parse_string("[1,2,3,]", err_handler);

    std::cout << val << std::endl;
}

