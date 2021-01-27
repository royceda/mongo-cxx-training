
#include <iostream>
#include <stdlib.h>
//#include <sqlite3.h>
#include <stdio.h>

#include <cstdlib>
#include <iostream>

#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

using bsoncxx::to_json;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

using namespace mongocxx;

using namespace std;

// to compile only
// c++ --std=c++11 connection.cpp \
//   -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 \
//   -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0 \
//   -L/usr/local/lib -lmongocxx -lbsoncxx

int main()
{
    std::cout << "Hello, world!\n";

    // The mongocxx::instance constructor and destructor initialize and shut down the driver,
    // respectively. Therefore, a mongocxx::instance must be created before using the driver and
    // must remain alive for as long as the driver is in use.

    instance instance{}; // This should be done only once.
    mongocxx::uri uri("mongodb://localhost:27017");
    mongocxx::client conn(uri);

    // By default, a session is causally consistent. Pass options::client_session to override
    // causal consistency.

    auto session = conn.start_session();
    auto collection = conn["mydb"]["test"];

    // create a document
    /*
        {
        "name" : "MongoDB",
        "type" : "database",
        "count" : 1,
        "versions": [ "v3.2", "v3.0", "v2.6" ],
        "info" : {
                    "x" : 203,
                    "y" : 102
                    }
        }
    */

    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
                                         << "name"
                                         << "MongoDB"
                                         << "type"
                                         << "database"
                                         << "count" << 1
                                         << "versions" << bsoncxx::builder::stream::open_array
                                         << "v3.2"
                                         << "v3.0"
                                         << "v2.6"
                                         << close_array
                                         << "info" << bsoncxx::builder::stream::open_document
                                         << "x" << 203
                                         << "y" << 102
                                         << bsoncxx::builder::stream::close_document
                                         << bsoncxx::builder::stream::finalize;

    bsoncxx::document::view view = doc_value.view();

    bsoncxx::document::element element = view["name"];
    if (element.type() != bsoncxx::type::k_utf8)
    {
        cout << "ERROR !!! " << endl;
    }
    else
    {
        std::string name = element.get_utf8().value.to_string();
        cout << name << endl;

        // print array
        for (auto msg : view["versions"].get_array().value)
        {
            cout << msg.get_utf8().value.to_string() << endl;
        }
    }

    // Insert document
    bsoncxx::document::value restaurant_doc = make_document(
        kvp("address",
            make_document(kvp("street", "2 Avenue"),
                          kvp("zipcode", 10075),
                          kvp("building", "1480"),
                          kvp("coord", make_array(-73.9557413, 40.7720266)))),
        kvp("borough", "Manhattan"),
        kvp("i", 76),
        kvp("cuisine", "Italian"),
        kvp("grades",
            make_array(
                make_document(kvp("date", bsoncxx::types::b_date{std::chrono::milliseconds{12323}}),
                              kvp("grade", "A"),
                              kvp("score", 11)),
                make_document(
                    kvp("date", bsoncxx::types::b_date{std::chrono::milliseconds{121212}}),
                    kvp("grade", "B"),
                    kvp("score", 17)))),
        kvp("name", "test1"),
        kvp("restaurant_id", "41704620"));

    auto res = collection.insert_one(std::move(restaurant_doc));

    // Find a single Document in a Collection
    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result = collection.find_one({});
    if (maybe_result)
    {
        std::cout << bsoncxx::to_json(maybe_result.value().view()) << endl;
        cout << "OK" << endl;
    }

    // Find all documents in a collection
    mongocxx::cursor cursor = collection.find({});
    for (auto doc : cursor) { cout << bsoncxx::to_json(doc) << endl; }

    // Specify a query
    maybe_result = collection.find_one(document{} << "name" << "reda" << finalize);
    if (maybe_result)
    {
        cout << "FROM QUERY : " << endl;
        cout << bsoncxx::to_json(*maybe_result) << endl;
    }

    // Get all documents that match a filter
    cursor = collection.find(
        document{} << "i" << open_document << "$gt" << 50 << "$lte" << 100
                   << close_document << finalize);
    for (auto doc : cursor)
    {
        std::cout << bsoncxx::to_json(doc) << endl;
    }

    // Update Documents
    // collection.update_one(document{} << "i" << 10 << finalize,
    //                       document{} << "$set" << open_document <<
    //                         "i" << 110 << close_document << finalize);

    // update multiple Documents
    // bsoncxx::stdx::optional<mongocxx::result::update> result =
    //  collection.update_many(
    //   document{} << "i" << open_document <<
    //     "$lt" << 100 << close_document << finalize,
    //   document{} << "$inc" << open_document <<
    //     "i" << 100 << close_document << finalize);

    // if(result) {
    //   std::cout << result->modified_count() << "\n";
    // }

    // Delete documents
    collection.delete_one(document{} << "name"
                                     << "test1" << finalize);

    // Create index 
    auto index_specification = document{} << "index" << 1 << finalize;
    collection.create_index(std::move(index_specification));

}