#include "cart.h"
#include "database.h"
#include "../config/config.h"

#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/MySQL/MySQLException.h>
#include <Poco/Data/SessionFactory.h>
#include <Poco/Data/RecordSet.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

#include <sstream>
#include <exception>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

namespace database
{

    void Cart::init()
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Statement create_stmt(session);
            create_stmt << "CREATE TABLE IF NOT EXISTS `Cart` (`id` INT NOT NULL AUTO_INCREMENT,"
                        << "`owner_id` INT NOT NULL,"
                        << "FOREIGN KEY (`owner_id`) REFERENCES `User` (`id`),"
                        << "PRIMARY KEY (`id`));",
                now;

        }

        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
            throw;
        }
            try
        {

            Poco::Data::Session session = database::Database::get().create_session();
            Statement create_stmt(session);
            create_stmt << "CREATE TABLE IF NOT EXISTS `Cart_Item` (`id` INT NOT NULL AUTO_INCREMENT,"
                        << "`cart_id` INT NOT NULL,"
                        << "`item_id` INT NOT NULL,"
                        << "`amount` INT NOT NULL,"
                        << "FOREIGN KEY (`cart_id`)  REFERENCES `Cart` (`id`),"
                        << "FOREIGN KEY (`item_id`)  REFERENCES `Item` (`id`),"
                        << "PRIMARY KEY (`id`));",
                        now;

        }

        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
            throw;
        }
    }

    Poco::JSON::Object::Ptr Cart::toJSON() const
    {
        Poco::JSON::Object::Ptr root = new Poco::JSON::Object();

        root->set("id", _id);
        root->set("owner_id", _owner_id);

        return root;
    }

    Cart Cart::fromJSON(const std::string &str)
    {
        Cart Cart;
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(str);
        Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();

        Cart.id() = object->getValue<long>("id");
        Cart.owner_id() = object->getValue<long>("owner_id");


        return Cart;
    }


    std::optional<Cart> Cart::read_by_id(long id)
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement select(session);
            Cart a;
            select << "SELECT id, owner_id FROM Cart where owner_id=?",
                into(a._id),
                into(a._owner_id),
                use(id),
                range(0, 1); //  iterate over result set one row at a time

            select.execute();
            Poco::Data::RecordSet rs(select);
            if (rs.moveFirst()) return a;
        }

        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
            
        }
        return {};
    }

    void Cart::add_item(long owner_id, long item_id, int amount)
    {
         try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement insert(session);
            long cart_id = read_by_id(owner_id).value().get_owner_id();
            insert << "INSERT INTO Cart_Item (cart_id, item_id, amount) VALUES(?, ?, ?)",
                use(cart_id);
                use(item_id),
                use(amount);
            insert.execute();
        }
            catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
            throw;
        }
    }

    void Cart::save_to_mysql()
    {

        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement insert(session);

            insert << "INSERT INTO Cart (owner_id) VALUES(?)",
                use(_owner_id);

            insert.execute();

            Poco::Data::Statement select(session);
            select << "SELECT LAST_INSERT_ID()",
                into(_id),
                range(0, 1); //  iterate over result set one row at a time

            if (!select.done())
            {
                select.execute();
            }
            std::cout << "inserted:" << _id << std::endl;
        }
        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
            throw;
        }
    }

 

    long Cart::get_id() const
    {
        return _id;
    }

    long &Cart::id()
    {
        return _id;
    }

        long Cart::get_owner_id() const
    {
        return _id;
    }

    long &Cart::owner_id()
    {
        return _id;
    }

    
}