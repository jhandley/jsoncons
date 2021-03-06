#include <jsoncons/json_parser.hpp>
#include <jsoncons/json_cursor.hpp>
#include <jsoncons/json.hpp>

using namespace jsoncons;
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
        std::string s(reinterpret_cast<const char*>(data), size);
        std::istringstream is(s);

        std::error_code ec;
        json_cursor reader(is, ec);
        while (reader.done() == 0 && !ec)
        {
                const auto& event = reader.current();
                std::string s2 = event.get<std::string>(ec);
                if (!ec)
                {
                    reader.next(ec);
                }
        }

        return 0;
}
