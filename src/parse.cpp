
#include <cpptoml.h>

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
List tomlparse(std::string filename) {

    cpptoml::table g = cpptoml::parse_file(filename);
    Rcpp::Rcout << "<print method>\n" 
                << g 
                << "</print method>\n" 
                << std::endl;

    Rcpp::List l;

    //for (cpptoml::table::iterator it = g.begin(); it != g.end(); it++) {
    for (auto & p : g) {

        if (p.second->is_table_array()) {
            Rcpp::Rcout << "TableArray: " << p.first << std::endl;
            l.push_front(p.first); // FIXME: want different operator
            auto ga = std::dynamic_pointer_cast<cpptoml::table_array>(p.second);
            //ga->print(stream, depth, p.first);
        } else if (p.second->is_table()) {
            Rcpp::Rcout << "Table: " << p.first << std::endl;
            l.push_front(p.first); // FIXME: want different operator
        } else if (p.second->is_array()) {
            Rcpp::Rcout << "Array: " << p.first << std::endl;
            l.push_front(p.first); // FIXME: want different operator
        } else {
            Rcpp::Rcout << "Other: " << p.first << std::endl;
            l.push_front(p.first); // FIXME: want different operator
        }
        //     else
        //     {
        //         stream << std::string(depth, '\t') << p.first << " = ";
        //         if (p.second->is_table())
        //         {
        //             auto g = static_cast<table*>(p.second.get());
        //             stream << '\n';
        //             g->print(stream, depth + 1);
        //         }
        //         else
        //         {
        //             p.second->print(stream);
        //             stream << '\n';
        //         }
        //     }


    }
    
    return l;
}
