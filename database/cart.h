#ifndef CART_H
#define CART_H

#include <string>
#include <vector>
#include "Poco/JSON/Object.h"
#include <optional>

namespace database
{
    class Cart{
        private:
            long _id;
            long _owner_id;

        public:

            static Cart fromJSON(const std::string & str);

            long             get_id() const;
            long             get_owner_id() const;

            long&        id();
            long&  owner_id();
    

            static void init();
            static std::optional<Cart> read_by_id(long id);
            void save_to_mysql();

            Poco::JSON::Object::Ptr toJSON() const;

    };
}

#endif