#include <soci/mysql/soci-mysql.h>
#include <soci/soci.h>

#include <exception>
#include <iostream>
#include <string>

template <typename T>
void get_data(const std::string prompt, T& value)
{
    std::cout << prompt;
    std::cin >> value;
}

void insert_user(soci::session& sql, const std::string& first_name,
                 const std::string& last_name, const std::string& email)
{
    sql << "INSERT INTO users(first_name, last_name, email) VALUES(:fn, :ln, "
           ":e)",
        soci::use(first_name, "fn"), soci::use(last_name, "ln"),
        soci::use(email, "e");

    std::cout << "> Successfully inserted user." << std::endl << std::endl;
}

void display_users(soci::session& sql)
{
    // Retrieve all rows.
    soci::rowset<soci::row> rs = (sql.prepare << "SELECT * FROM users");

    // Iterate through the result set.
    for (soci::rowset<soci::row>::const_iterator it = rs.begin();
         it != rs.end(); ++it) {
        const soci::row& r = *it;
        std::cout << "ID: " << r.get<int>(0) << std::endl
                  << "First Name: " << r.get<std::string>(1) << std::endl
                  << "Last Name: " << r.get<std::string>(2) << std::endl
                  << "Email: " << r.get<std::string>(3) << std::endl
                  << "Active: " << r.get<int>(4) << std::endl;
    }
}

int main()
{
    try {
        // Connect to DB.
        soci::session sql(soci::mysql,
                          "db=soci_db user=deepb password=password");

        // Get data for new user.
        std::string first_name, last_name, email;

        get_data("> Enter your first name: ", first_name);
        get_data("> Enter your last name: ", last_name);
        get_data("> Enter your email: ", email);

        // Insert into database.
        insert_user(sql, first_name, last_name, email);

        // Display users.
        display_users(sql);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}