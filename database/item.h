#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>
#include <vector>
#include "Poco/JSON/Object.h"
#include <optional>

namespace database
{
    class Item{
        private:
            long _id;
            std::string _name;
            std::string _type;
            std::string _description;
            int _price;

        public:

            static Item fromJSON(const std::string & str);

            long             get_id() const;
            const std::string &get_name() const;
            const std::string &get_type() const;
            const std::string &get_description() const;
            int             get_price() const;

            long&        id();
            std::string& name();
            std::string& type();
            std::string& description();
            int&  price();
    

            static void init();
            static std::optional<Item> read_by_id(long id);
            static std::vector<Item> read_all();
            void save_to_mysql();

            Poco::JSON::Object::Ptr toJSON() const;

    };
}

#endif