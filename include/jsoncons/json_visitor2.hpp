// Copyright 2018 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://github.com/danielaparker/jsoncons for latest version

#ifndef JSONCONS_JSON_VISITOR2_HPP
#define JSONCONS_JSON_VISITOR2_HPP

#include <jsoncons/json_visitor.hpp>
#include <jsoncons/json_encoder.hpp>

namespace jsoncons { 

    template <class CharT>
    class basic_json_visitor2_to_json_visitor;

    template <class CharT>
    class basic_json_visitor2 
    {
        friend class basic_json_visitor2_to_json_visitor<CharT>;
    public:
        using char_type = CharT;
        using char_traits_type = std::char_traits<char_type>;

        using string_view_type = basic_string_view<char_type,char_traits_type>;

        basic_json_visitor2(basic_json_visitor2&&) = default;

        basic_json_visitor2& operator=(basic_json_visitor2&&) = default;

        basic_json_visitor2() = default;

        virtual ~basic_json_visitor2() noexcept = default;

        void flush()
        {
            visit_flush();
        }

        bool begin_object(semantic_tag tag=semantic_tag::none,
                          const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_begin_object(tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool begin_object(std::size_t length, 
                          semantic_tag tag=semantic_tag::none, 
                          const ser_context& context = ser_context())
        {
            std::error_code ec;
            bool more = visit_begin_object(length, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool end_object(const ser_context& context = ser_context())
        {
            std::error_code ec;
            bool more = visit_end_object(context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool begin_array(semantic_tag tag=semantic_tag::none,
                         const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_begin_array(tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool begin_array(std::size_t length, 
                         semantic_tag tag=semantic_tag::none,
                         const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_begin_array(length, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool end_array(const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_end_array(context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool key(const string_view_type& name, const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_string(name, semantic_tag::none, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool null_value(semantic_tag tag = semantic_tag::none,
                        const ser_context& context=ser_context()) 
        {
            std::error_code ec;
            bool more = visit_null(tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool bool_value(bool value, 
                        semantic_tag tag = semantic_tag::none,
                        const ser_context& context=ser_context()) 
        {
            std::error_code ec;
            bool more = visit_bool(value, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool string_value(const string_view_type& value, 
                          semantic_tag tag = semantic_tag::none, 
                          const ser_context& context=ser_context()) 
        {
            std::error_code ec;
            bool more = visit_string(value, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool byte_string_value(const byte_string_view& b, 
                               semantic_tag tag=semantic_tag::none, 
                               const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_byte_string(b, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool byte_string_value(const uint8_t* p, std::size_t size, 
                               semantic_tag tag=semantic_tag::none, 
                               const ser_context& context=ser_context())
        {
            return byte_string_value(byte_string(p, size), tag, context);
        }

        bool uint64_value(uint64_t value, 
                          semantic_tag tag = semantic_tag::none, 
                          const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_uint64(value, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool int64_value(int64_t value, 
                         semantic_tag tag = semantic_tag::none, 
                         const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_int64(value, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool half_value(uint16_t value, 
                        semantic_tag tag = semantic_tag::none, 
                        const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_half(value, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool double_value(double value, 
                          semantic_tag tag = semantic_tag::none, 
                          const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_double(value, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool begin_object(semantic_tag tag,
                          const ser_context& context,
                          std::error_code& ec)
        {
            return visit_begin_object(tag, context, ec);
        }

        bool begin_object(std::size_t length, 
                          semantic_tag tag, 
                          const ser_context& context,
                          std::error_code& ec)
        {
            return visit_begin_object(length, tag, context, ec);
        }

        bool end_object(const ser_context& context, std::error_code& ec)
        {
            return visit_end_object(context, ec);
        }

        bool begin_array(semantic_tag tag, const ser_context& context, std::error_code& ec)
        {
            return visit_begin_array(tag, context, ec);
        }

        bool begin_array(std::size_t length, semantic_tag tag, const ser_context& context, std::error_code& ec)
        {
            return visit_begin_array(length, tag, context, ec);
        }

        bool end_array(const ser_context& context, std::error_code& ec)
        {
            return visit_end_array(context, ec);
        }

        bool key(const string_view_type& name, const ser_context& context, std::error_code& ec)
        {
            return visit_string(name, semantic_tag::none, context, ec);
        }

        bool null_value(semantic_tag tag,
                        const ser_context& context,
                        std::error_code& ec) 
        {
            return visit_null(tag, context, ec);
        }

        bool bool_value(bool value, 
                        semantic_tag tag,
                        const ser_context& context,
                        std::error_code& ec) 
        {
            return visit_bool(value, tag, context, ec);
        }

        bool string_value(const string_view_type& value, 
                          semantic_tag tag, 
                          const ser_context& context,
                          std::error_code& ec) 
        {
            return visit_string(value, tag, context, ec);
        }

        bool byte_string_value(const byte_string_view& b, 
                               semantic_tag tag, 
                               const ser_context& context,
                               std::error_code& ec)
        {
            return visit_byte_string(b, tag, context, ec);
        }

        bool byte_string_value(const uint8_t* p, std::size_t size, 
                               semantic_tag tag, 
                               const ser_context& context,
                               std::error_code& ec)
        {
            return byte_string_value(byte_string(p, size), tag, context, ec);
        }

        bool uint64_value(uint64_t value, 
                          semantic_tag tag, 
                          const ser_context& context,
                          std::error_code& ec)
        {
            return visit_uint64(value, tag, context, ec);
        }

        bool int64_value(int64_t value, 
                         semantic_tag tag, 
                         const ser_context& context,
                         std::error_code& ec)
        {
            return visit_int64(value, tag, context, ec);
        }

        bool half_value(uint16_t value, 
                        semantic_tag tag, 
                        const ser_context& context,
                        std::error_code& ec)
        {
            return visit_half(value, tag, context, ec);
        }

        bool double_value(double value, 
                          semantic_tag tag, 
                          const ser_context& context,
                          std::error_code& ec)
        {
            return visit_double(value, tag, context, ec);
        }

        template <class T>
        bool typed_array(const span<T>& data, 
                         semantic_tag tag=semantic_tag::none,
                         const ser_context& context=ser_context())
        {
            std::error_code ec;
            bool more = visit_typed_array(data, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        template <class T>
        bool typed_array(const span<T>& data, 
                         semantic_tag tag,
                         const ser_context& context,
                         std::error_code& ec)
        {
            return visit_typed_array(data, tag, context, ec);
        }

        bool typed_array(half_arg_t, const span<const uint16_t>& s,
            semantic_tag tag = semantic_tag::none,
            const ser_context& context = ser_context())
        {
            std::error_code ec;
            bool more = visit_typed_array(half_arg, s, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool typed_array(half_arg_t, const span<const uint16_t>& s,
                         semantic_tag tag,
                         const ser_context& context,
                         std::error_code& ec)
        {
            return visit_typed_array(half_arg, s, tag, context, ec);
        }

        bool begin_multi_dim(const span<const size_t>& shape,
                             semantic_tag tag = semantic_tag::multi_dim_row_major,
                             const ser_context& context=ser_context()) 
        {
            std::error_code ec;
            bool more = visit_begin_multi_dim(shape, tag, context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool begin_multi_dim(const span<const size_t>& shape,
                             semantic_tag tag,
                             const ser_context& context,
                             std::error_code& ec) 
        {
            return visit_begin_multi_dim(shape, tag, context, ec);
        }

        bool end_multi_dim(const ser_context& context=ser_context()) 
        {
            std::error_code ec;
            bool more = visit_end_multi_dim(context, ec);
            if (ec)
            {
                JSONCONS_THROW(ser_error(ec, context.line(), context.column()));
            }
            return more;
        }

        bool end_multi_dim(const ser_context& context,
                           std::error_code& ec) 
        {
            return visit_end_multi_dim(context, ec);
        }

    private:

        virtual void visit_flush() = 0;

        virtual bool visit_begin_object(semantic_tag tag, 
                                     const ser_context& context, 
                                     std::error_code& ec) = 0;

        virtual bool visit_begin_object(std::size_t /*length*/, 
                                     semantic_tag tag, 
                                     const ser_context& context, 
                                     std::error_code& ec)
        {
            return visit_begin_object(tag, context, ec);
        }

        virtual bool visit_end_object(const ser_context& context, 
                                   std::error_code& ec) = 0;

        virtual bool visit_begin_array(semantic_tag tag, 
                                    const ser_context& context, 
                                    std::error_code& ec) = 0;

        virtual bool visit_begin_array(std::size_t /*length*/, 
                                    semantic_tag tag, 
                                    const ser_context& context, 
                                    std::error_code& ec)
        {
            return visit_begin_array(tag, context, ec);
        }

        virtual bool visit_end_array(const ser_context& context, 
                                  std::error_code& ec) = 0;

        virtual bool visit_null(semantic_tag tag, 
                             const ser_context& context, 
                             std::error_code& ec) = 0;

        virtual bool visit_bool(bool value, 
                             semantic_tag tag, 
                             const ser_context& context, 
                             std::error_code&) = 0;

        virtual bool visit_string(const string_view_type& value, 
                               semantic_tag tag, 
                               const ser_context& context, 
                               std::error_code& ec) = 0;

        virtual bool visit_byte_string(const byte_string_view& value, 
                                    semantic_tag tag, 
                                    const ser_context& context,
                                    std::error_code& ec) = 0;

        virtual bool visit_uint64(uint64_t value, 
                               semantic_tag tag, 
                               const ser_context& context,
                               std::error_code& ec) = 0;

        virtual bool visit_int64(int64_t value, 
                              semantic_tag tag,
                              const ser_context& context,
                              std::error_code& ec) = 0;

        virtual bool visit_half(uint16_t value, 
                             semantic_tag tag,
                             const ser_context& context,
                             std::error_code& ec)
        {
            return visit_double(jsoncons::detail::decode_half(value),
                             tag,
                             context,
                             ec);
        }

        virtual bool visit_double(double value, 
                               semantic_tag tag,
                               const ser_context& context,
                               std::error_code& ec) = 0;

        virtual bool visit_typed_array(const span<const uint8_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec)  
        {
            bool more = begin_array(s.size(), tag, context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = uint64_value(*p, semantic_tag::none, context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(const span<const uint16_t>& s, 
                                    semantic_tag tag, 
                                    const ser_context& context, 
                                    std::error_code& ec)  
        {
            bool more = begin_array(s.size(), tag, context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = uint64_value(*p, semantic_tag::none, context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(const span<const uint32_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec) 
        {
            bool more = begin_array(s.size(), tag, context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = uint64_value(*p, semantic_tag::none, context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(const span<const uint64_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec) 
        {
            bool more = begin_array(s.size(), tag, context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = uint64_value(*p,semantic_tag::none,context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(const span<const int8_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec)  
        {
            bool more = begin_array(s.size(), tag,context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = int64_value(*p,semantic_tag::none,context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(const span<const int16_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec)  
        {
            bool more = begin_array(s.size(), tag,context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = int64_value(*p,semantic_tag::none,context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(const span<const int32_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec)  
        {
            bool more = begin_array(s.size(), tag,context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = int64_value(*p,semantic_tag::none,context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(const span<const int64_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec)  
        {
            bool more = begin_array(s.size(), tag,context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = int64_value(*p,semantic_tag::none,context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(half_arg_t, 
                                    const span<const uint16_t>& s, 
                                    semantic_tag tag, 
                                    const ser_context& context, 
                                    std::error_code& ec)  
        {
            bool more = begin_array(s.size(), tag, context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = half_value(*p, semantic_tag::none, context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(const span<const float>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec)  
        {
            bool more = begin_array(s.size(), tag,context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = double_value(*p,semantic_tag::none,context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_typed_array(const span<const double>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec)  
        {
            bool more = begin_array(s.size(), tag,context, ec);
            for (auto p = s.begin(); more && p != s.end(); ++p)
            {
                more = double_value(*p,semantic_tag::none,context, ec);
            }
            if (more)
            {
                more = end_array(context, ec);
            }
            return more;
        }

        virtual bool visit_begin_multi_dim(const span<const size_t>& shape,
                                        semantic_tag tag,
                                        const ser_context& context, 
                                        std::error_code& ec) 
        {
            bool more = visit_begin_array(2, tag, context, ec);
            if (more)
            {
                more = visit_begin_array(shape.size(), tag, context, ec);
                for (auto it = shape.begin(); more && it != shape.end(); ++it)
                {
                    visit_uint64(*it, semantic_tag::none, context, ec);
                }
                if (more)
                {
                    more = visit_end_array(context, ec);
                }
            }
            return more;
        }

        virtual bool visit_end_multi_dim(const ser_context& context,
                                      std::error_code& ec) 
        {
            return visit_end_array(context, ec);
        }
    };

    template <class CharT>
    class basic_json_visitor2_to_json_visitor : public basic_json_visitor2<CharT>
    {
    public:
        using typename basic_json_visitor2<CharT>::char_type;
        using typename basic_json_visitor2<CharT>::string_view_type;
    private:

        using string_type = std::basic_string<CharT>;

        enum class container_t {root, array, object};
        enum class output_t {destination, key_buffer};

        struct level
        {
        private:
            output_t state_;
            container_t type_;
            int even_odd_;
            std::size_t count_;
        public:

            level(output_t state, container_t type)
                : state_(state), type_(type), even_odd_(type == container_t::object ? 0 : 1), count_(0)
            {
            }

            void advance()
            {
                if (!is_key())
                {
                    ++count_;
                }
                if (is_object())
                {
                    even_odd_ = !even_odd_;
                }
            }

            bool is_key() const
            {
                return even_odd_ == 0;
            }

            bool is_object() const
            {
                return type_ == container_t::object;
            }

            output_t write_to() const
            {
                return state_;
            }

            std::size_t count() const
            {
                return count_;
            }
        };

        basic_json_visitor<char_type>& destination_;
        string_type key_;
        string_type key_buffer_;
        std::vector<level> level_stack_;

        const string_type null_k = {'n','u','l','l'};
        const string_type true_k = { 't','r','u','e' };
        const string_type false_k = { 'f', 'a', 'l', 's', 'e' };

        // noncopyable and nonmoveable
        basic_json_visitor2_to_json_visitor(const basic_json_visitor2_to_json_visitor&) = delete;
        basic_json_visitor2_to_json_visitor& operator=(const basic_json_visitor2_to_json_visitor&) = delete;
    public:
        basic_json_visitor2_to_json_visitor(basic_json_visitor<char_type>& visitor)
            : destination_(visitor)
        {
            level_stack_.emplace_back(output_t::destination,container_t::root); // root
        }

        basic_json_visitor<char_type>& destination()
        {
            return destination_;
        }

    private:
        void visit_flush() override
        {
            destination_.flush();
        }

        bool visit_begin_object(semantic_tag tag, const ser_context& context, std::error_code& ec) override
        {
            if (level_stack_.back().is_key())
            {
                level_stack_.emplace_back(output_t::key_buffer, container_t::object);
                key_buffer_.push_back('{');
                return true;
            }
            else
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        level_stack_.emplace_back(output_t::key_buffer, container_t::object);
                        key_buffer_.push_back('{');
                        return true;
                    default:
                        level_stack_.emplace_back(output_t::destination, container_t::object);
                        return destination_.begin_object(tag, context, ec);
                }
            }
        }

        bool visit_begin_object(std::size_t length, semantic_tag tag, const ser_context& context, std::error_code& ec) override
        {
            if (level_stack_.back().is_key())
            {
                if (level_stack_.back().is_object() && !key_buffer_.empty())
                {
                    key_buffer_.push_back(',');
                }
                level_stack_.emplace_back(output_t::key_buffer, container_t::object);
                key_buffer_.push_back('{');
                return true;
            }
            else
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (!level_stack_.back().is_object() && !key_buffer_.empty())
                        {
                            key_buffer_.push_back(',');
                        }
                        level_stack_.emplace_back(output_t::key_buffer, container_t::object);
                        key_buffer_.push_back('{');
                        return true;
                    default:
                        level_stack_.emplace_back(output_t::destination, container_t::object);
                        return destination_.begin_object(length, tag, context, ec);
                }
            }
        }

        bool visit_end_object(const ser_context& context, std::error_code& ec) override
        {
            bool ret = true;
            switch (level_stack_.back().write_to())
            {
                case output_t::key_buffer:
                    key_buffer_.push_back('}');
                    level_stack_.pop_back();
                    
                    if (level_stack_.back().write_to() == output_t::destination)
                    {
                        ret = destination_.key(key_buffer_,context, ec);
                        key_buffer_.clear();
                    }
                    else if (level_stack_.back().is_key())
                    {
                        key_buffer_.push_back(':');
                    }
                    level_stack_.back().advance();
                    break;
                default:
                    if (level_stack_.size() > 1)
                    {
                        level_stack_.pop_back();
                        level_stack_.back().advance();
                    }
                    ret = destination_.end_object(context, ec);
                    break;
            }
            return ret;
        }

        bool visit_begin_array(semantic_tag tag, const ser_context& context, std::error_code& ec) override
        {
            if (level_stack_.back().is_key())
            {
                if (level_stack_.back().is_object() && !key_buffer_.empty())
                {
                    key_buffer_.push_back(',');
                }
                level_stack_.emplace_back(output_t::key_buffer, container_t::array);
                key_buffer_.push_back('[');
                return true;
            }
            else
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (level_stack_.back().is_object() && !key_buffer_.empty())
                        {
                            key_buffer_.push_back(',');
                        }
                        level_stack_.emplace_back(output_t::key_buffer, container_t::array);
                        key_buffer_.push_back('[');
                        return true;
                    default:
                        level_stack_.emplace_back(output_t::destination, container_t::array);
                        return destination_.begin_array(tag, context, ec);
                }
            }
        }

        bool visit_begin_array(std::size_t length, semantic_tag tag, const ser_context& context, std::error_code& ec) override
        {
            if (level_stack_.back().is_key())
            {
                if (level_stack_.back().is_object() && !key_buffer_.empty())
                {
                    key_buffer_.push_back(',');
                }
                level_stack_.emplace_back(output_t::key_buffer, container_t::array);
                key_buffer_.push_back('[');
                return true;
            }
            else
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (!level_stack_.back().is_object() && !key_buffer_.empty())
                        {
                            key_buffer_.push_back(',');
                        }
                        level_stack_.emplace_back(output_t::key_buffer, container_t::array);
                        key_buffer_.push_back('[');
                        return true;
                    default:
                        level_stack_.emplace_back(output_t::destination, container_t::array);
                        return destination_.begin_array(length, tag, context, ec);
                }
            }
        }

        bool visit_end_array(const ser_context& context, std::error_code& ec) override
        {
            bool ret = true;
            switch (level_stack_.back().write_to())
            {
                case output_t::key_buffer:
                    key_buffer_.push_back(']');
                    level_stack_.pop_back();
                    if (level_stack_.back().write_to() == output_t::destination)
                    {
                        ret = destination_.key(key_buffer_, context, ec);
                        key_buffer_.clear();
                    }
                    else if (level_stack_.back().is_key())
                    {
                        key_buffer_.push_back(':');
                    }
                    level_stack_.back().advance();
                    break;
                default:
                    if (level_stack_.size() > 1)
                    {
                        level_stack_.pop_back();
                        level_stack_.back().advance();
                    }
                    ret = destination_.end_array(context, ec);
                    break;
            }
            return ret;
        }

        bool visit_string(const string_view_type& value,
                             semantic_tag tag,
                             const ser_context& context,
                             std::error_code& ec) override
        {
            bool ret = true;

            if (level_stack_.back().is_key())
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (level_stack_.back().count() > 0)
                        {
                            key_buffer_.push_back(',');
                        }
                        key_buffer_.push_back('\"');
                        key_buffer_.insert(key_buffer_.end(), value.begin(), value.end());
                        key_buffer_.push_back('\"');
                        key_buffer_.push_back(':');
                        ret = true;
                        break;
                    default:
                        ret = destination_.key(value, context, ec);
                        break;
                }
            }
            else
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (!level_stack_.back().is_object() && level_stack_.back().count() > 0)
                        {
                            key_buffer_.push_back(',');
                        }
                        key_buffer_.push_back('\"');
                        key_buffer_.insert(key_buffer_.end(), value.begin(), value.end());
                        key_buffer_.push_back('\"');
                        ret = true;
                        break;
                    default:
                        ret = destination_.string_value(value, tag, context, ec);
                        break;
                }
            }

            level_stack_.back().advance();
            return ret;
        }

        bool visit_byte_string(const byte_string_view& value, 
                                  semantic_tag tag,
                                  const ser_context& context,
                                  std::error_code& ec) override
        {
            bool ret = true;

            if (level_stack_.back().is_key() || level_stack_.back().write_to() == output_t::key_buffer)
            {
                key_.clear();
                switch (tag)
                {
                    case semantic_tag::base64:
                        encode_base64(value.begin(), value.end(), key_);
                        break;
                    case semantic_tag::base16:
                        encode_base16(value.begin(), value.end(),key_);
                        break;
                    default:
                        encode_base64url(value.begin(), value.end(),key_);
                        break;
                }
            }

            if (level_stack_.back().is_key())
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (level_stack_.back().count() > 0)
                        {
                            key_buffer_.push_back(',');
                        }
                        key_buffer_.push_back('\"');
                        key_buffer_.insert(key_buffer_.end(), key_.begin(), key_.end());
                        key_buffer_.push_back('\"');
                        key_buffer_.push_back(':');
                        ret = true; 
                        break;
                    default:
                        ret = destination_.key(key_, context, ec);
                        break;
                }
            }
            else
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (!level_stack_.back().is_object() && level_stack_.back().count() > 0)
                        {
                            key_buffer_.push_back(',');
                        }
                        key_buffer_.push_back('\"');
                        key_buffer_.insert(key_buffer_.end(), key_.begin(), key_.end());
                        key_buffer_.push_back('\"');
                        ret = true; 
                        break;
                    default:
                        ret = destination_.byte_string_value(value, tag, context, ec);
                        break;
                }
            }

            level_stack_.back().advance();
            return ret;
        }

        bool visit_uint64(uint64_t value, semantic_tag tag, const ser_context& context, std::error_code& ec) override
        {
            bool ret = true;

            if (level_stack_.back().is_key() || level_stack_.back().write_to() == output_t::key_buffer)
            {
                key_.clear();
                jsoncons::detail::write_integer(value,key_);
            }

            if (level_stack_.back().is_key())
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (level_stack_.back().count() > 0)
                        {
                            key_buffer_.push_back(',');
                        }
                        key_buffer_.insert(key_buffer_.end(), key_.begin(), key_.end());
                        key_buffer_.push_back(':');
                        ret = true; 
                        break;
                    default:
                        ret = destination_.key(key_, context, ec);
                        break;
                }
            }
            else
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (!level_stack_.back().is_object() && level_stack_.back().count() > 0)
                        {
                            key_buffer_.push_back(',');
                        }
                        key_buffer_.insert(key_buffer_.end(), key_.begin(), key_.end());
                        ret = true; 
                        break;
                    default:
                        ret = destination_.uint64_value(value, tag, context, ec);
                        break;
                }
            }

            level_stack_.back().advance();
            return ret;
        }

        bool visit_int64(int64_t value, semantic_tag tag, const ser_context& context, std::error_code& ec) override
        {
            bool ret = true;

            if (level_stack_.back().is_key() || level_stack_.back().write_to() == output_t::key_buffer)
            {
                key_.clear();
                jsoncons::detail::write_integer(value,key_);
            }

            if (level_stack_.back().is_key())
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (level_stack_.back().count() > 0)
                        {
                            key_buffer_.push_back(',');
                        }
                        key_buffer_.insert(key_buffer_.end(), key_.begin(), key_.end());
                        key_buffer_.push_back(':');
                        ret = true; 
                        break;
                    default:
                        ret = destination_.key(key_, context, ec);
                        break;
                }
            }
            else
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (!level_stack_.back().is_object() && level_stack_.back().count() > 0)
                        {
                            key_buffer_.push_back(',');
                        }
                        key_buffer_.insert(key_buffer_.end(), key_.begin(), key_.end());
                        ret = true; 
                        break;
                    default:
                        ret = destination_.int64_value(value, tag, context, ec);
                        break;
                }
            }

            level_stack_.back().advance();
            return ret;
        }

        bool visit_half(uint16_t value, semantic_tag tag, const ser_context& context, std::error_code& ec) override
        {
            bool ret = true;

            if (level_stack_.back().is_key() || level_stack_.back().write_to() == output_t::key_buffer)
            {
                key_.clear();
                jsoncons::string_sink<string_type> sink(key_);
                jsoncons::detail::write_double f{float_chars_format::general,0};
                double x = jsoncons::detail::decode_half(value);
                f(x, sink);
            }

            if (level_stack_.back().is_key())
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (level_stack_.back().count() > 0)
                        {
                            key_buffer_.push_back(',');
                        }
                        key_buffer_.insert(key_buffer_.end(), key_.begin(), key_.end());
                        key_buffer_.push_back(':');
                        ret = true; 
                        break;
                    default:
                        ret = destination_.key(key_, context, ec);
                        break;
                }
            }
            else
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (!level_stack_.back().is_object() && level_stack_.back().count() > 0)
                        {
                            key_buffer_.push_back(',');
                        }
                        key_buffer_.insert(key_buffer_.end(), key_.begin(), key_.end());
                        ret = true; 
                        break;
                    default:
                        ret = destination_.half_value(value, tag, context, ec);
                        break;
                }
            }

            level_stack_.back().advance();
            return ret;
        }

        bool visit_double(double value, semantic_tag tag, const ser_context& context, std::error_code& ec) override
        {
            bool ret = true;

            if (level_stack_.back().is_key() || level_stack_.back().write_to() == output_t::key_buffer)
            {
                key_.clear();
                string_sink<string_type> sink(key_);
                jsoncons::detail::write_double f{float_chars_format::general,0};
                f(value, sink);
            }

            if (level_stack_.back().is_key())
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (level_stack_.back().count() > 0)
                        {
                            key_buffer_.push_back(',');
                        }
                        key_buffer_.insert(key_buffer_.end(), key_.begin(), key_.end());
                        key_buffer_.push_back(':');
                        ret = true; 
                        break;
                    default:
                        ret = destination_.key(key_, context, ec);
                        break;
                }
            }
            else
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (!level_stack_.back().is_object() && level_stack_.back().count() > 0)
                        {
                            key_buffer_.push_back(',');
                        }
                        key_buffer_.insert(key_buffer_.end(), key_.begin(), key_.end());
                        ret = true; 
                        break;
                    default:
                        ret = destination_.double_value(value, tag, context, ec);
                        break;
                }
            }

            level_stack_.back().advance();
            return ret;
        }

        bool visit_bool(bool value, semantic_tag tag, const ser_context& context, std::error_code& ec) override
        {
            bool ret = true;

            if (level_stack_.back().is_key() || level_stack_.back().write_to() == output_t::key_buffer)
            {
                key_ = value ? true_k : false_k;
            }

            if (level_stack_.back().is_key())
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (level_stack_.back().count() > 0)
                        {
                            key_buffer_.push_back(',');
                        }
                        key_buffer_.insert(key_buffer_.end(), key_.begin(), key_.end());
                        key_buffer_.push_back(':');
                        ret = true; 
                        break;
                    default:
                        ret = destination_.key(key_, context, ec);
                        break;
                }
            }
            else
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (!level_stack_.back().is_object() && level_stack_.back().count() > 0)
                        {
                            key_buffer_.push_back(',');
                        }
                        key_buffer_.insert(key_buffer_.end(), key_.begin(), key_.end());
                        ret = true; 
                        break;
                    default:
                        ret = destination_.bool_value(value, tag, context, ec);
                        break;
                }
            }

            level_stack_.back().advance();
            return ret;
        }

        bool visit_null(semantic_tag tag, const ser_context& context, std::error_code& ec) override
        {
            bool ret = true;

            if (level_stack_.back().is_key() || level_stack_.back().write_to() == output_t::key_buffer)
            {
                key_ = null_k;
            }

            if (level_stack_.back().is_key())
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (level_stack_.back().count() > 0)
                        {
                            key_buffer_.push_back(',');
                        }
                        key_buffer_.insert(key_buffer_.end(), key_.begin(), key_.end());
                        key_buffer_.push_back(':');
                        ret = true; 
                        break;
                    default:
                        ret = destination_.key(key_, context, ec);
                        break;
                }
            }
            else
            {
                switch (level_stack_.back().write_to())
                {
                    case output_t::key_buffer:
                        if (!level_stack_.back().is_object() && level_stack_.back().count() > 0)
                        {
                            key_buffer_.push_back(',');
                        }
                        key_buffer_.insert(key_buffer_.end(), key_.begin(), key_.end());
                        ret = true; 
                        break;
                    default:
                        ret = destination_.null_value(tag, context, ec);
                        break;
                }
            }

            level_stack_.back().advance();
            return ret;
        }

        bool visit_typed_array(const span<const uint8_t>& s, 
                               semantic_tag tag,
                               const ser_context& context, 
                               std::error_code& ec) override 
        {
            bool is_key = level_stack_.back().is_key();
            level_stack_.back().advance();

            if (is_key || level_stack_.back().write_to() == output_t::key_buffer)
            {
                return basic_json_visitor2<CharT>::visit_typed_array(s,tag,context,ec);
            }
            else
            {
                return destination_.typed_array(s, tag, context, ec);
            }
        }

        bool visit_typed_array(const span<const uint16_t>& s, 
                                    semantic_tag tag, 
                                    const ser_context& context, 
                                    std::error_code& ec) override  
        {
            bool is_key = level_stack_.back().is_key();
            level_stack_.back().advance();

            if (is_key || level_stack_.back().write_to() == output_t::key_buffer)
            {
                return basic_json_visitor2<CharT>::visit_typed_array(s,tag,context,ec);
            }
            else
            {
                return destination_.typed_array(s, tag, context, ec);
            }
        }

        bool visit_typed_array(const span<const uint32_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec) override 
        {
            bool is_key = level_stack_.back().is_key();
            level_stack_.back().advance();

            if (is_key || level_stack_.back().write_to() == output_t::key_buffer)
            {
                return basic_json_visitor2<CharT>::visit_typed_array(s,tag,context,ec);
            }
            else
            {
                return destination_.typed_array(s, tag, context, ec);
            }
        }

        bool visit_typed_array(const span<const uint64_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec) override 
        {
            bool is_key = level_stack_.back().is_key();
            level_stack_.back().advance();

            if (is_key || level_stack_.back().write_to() == output_t::key_buffer)
            {
                return basic_json_visitor2<CharT>::visit_typed_array(s,tag,context,ec);
            }
            else
            {
                return destination_.typed_array(s, tag, context, ec);
            }
        }

        bool visit_typed_array(const span<const int8_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec) override  
        {
            bool is_key = level_stack_.back().is_key();
            level_stack_.back().advance();

            if (is_key || level_stack_.back().write_to() == output_t::key_buffer)
            {
                return basic_json_visitor2<CharT>::visit_typed_array(s,tag,context,ec);
            }
            else
            {
                return destination_.typed_array(s, tag, context, ec);
            }
        }

        bool visit_typed_array(const span<const int16_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec) override  
        {
            bool is_key = level_stack_.back().is_key();
            level_stack_.back().advance();

            if (is_key || level_stack_.back().write_to() == output_t::key_buffer)
            {
                return basic_json_visitor2<CharT>::visit_typed_array(s,tag,context,ec);
            }
            else
            {
                return destination_.typed_array(s, tag, context, ec);
            }
        }

        bool visit_typed_array(const span<const int32_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec) override  
        {
            bool is_key = level_stack_.back().is_key();
            level_stack_.back().advance();

            if (is_key || level_stack_.back().write_to() == output_t::key_buffer)
            {
                return basic_json_visitor2<CharT>::visit_typed_array(s,tag,context,ec);
            }
            else
            {
                return destination_.typed_array(s, tag, context, ec);
            }
        }

        bool visit_typed_array(const span<const int64_t>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec) override  
        {
            bool is_key = level_stack_.back().is_key();
            level_stack_.back().advance();

            if (is_key || level_stack_.back().write_to() == output_t::key_buffer)
            {
                return basic_json_visitor2<CharT>::visit_typed_array(s,tag,context,ec);
            }
            else
            {
                return destination_.typed_array(s, tag, context, ec);
            }
        }

        bool visit_typed_array(half_arg_t, 
                               const span<const uint16_t>& s, 
                               semantic_tag tag, 
                               const ser_context& context, 
                               std::error_code& ec) override  
        {
            bool is_key = level_stack_.back().is_key();
            level_stack_.back().advance();

            if (is_key || level_stack_.back().write_to() == output_t::key_buffer)
            {
                return basic_json_visitor2<CharT>::visit_typed_array(half_arg,s,tag,context,ec);
            }
            else
            {
                return destination_.typed_array(half_arg, s, tag, context, ec);
            }
        }

        bool visit_typed_array(const span<const float>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec) override  
        {
            bool is_key = level_stack_.back().is_key();
            level_stack_.back().advance();

            if (is_key || level_stack_.back().write_to() == output_t::key_buffer)
            {
                return basic_json_visitor2<CharT>::visit_typed_array(s,tag,context,ec);
            }
            else
            {
                return destination_.typed_array(s, tag, context, ec);
            }
        }

        bool visit_typed_array(const span<const double>& s, 
                                    semantic_tag tag,
                                    const ser_context& context, 
                                    std::error_code& ec) override  
        {
            bool is_key = level_stack_.back().is_key();
            level_stack_.back().advance();

            if (is_key || level_stack_.back().write_to() == output_t::key_buffer)
            {
                return basic_json_visitor2<CharT>::visit_typed_array(s,tag,context,ec);
            }
            else
            {
                return destination_.typed_array(s, tag, context, ec);
            }
        }
    };

    using json_visitor2 = basic_json_visitor2<char>;
    using json_visitor2_to_json_visitor = basic_json_visitor2_to_json_visitor<char>;


} // namespace jsoncons

#endif