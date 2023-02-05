# Database Connection with C++

Follow the [tutorial](https://dane-bulat.medium.com/working-with-databases-in-c-an-introduction-7d6a6a78ae66).

## Install and configuring MySQL

[Installing MySQL](https://www.digitalocean.com/community/tutorials/how-to-install-mysql-on-ubuntu-20-04)

```bash
sudo apt update
sudo apt install mysql-server
```

We also need a [new super user](https://www.digitalocean.com/community/tutorials/how-to-create-a-new-user-and-grant-permissions-in-mysql)

```bash
sudo mysql -u root -p
CREATE USER 'sammy'@'localhost' IDENTIFIED BY 'password';
GRANT ALL PRIVILEGES ON *.* TO 'sammy'@'localhost' WITH GRANT OPTION;
```

Finally install the mysql libs:

```bash
sudo apt install libmysqlclient-dev
```

## Installing SOCI

[Installing](https://soci.sourceforge.net/doc/master/installation/) SOCI is straightforward.

## Download SOCI
```bash
git clone git://github.com/SOCI/soci.git
# wget https://sourceforge.net/projects/soci/files/soci/soci-4.0.3/soci-4.0.3.tar.gz
# tar -xvcf soci-4.0.3.tar.gz
```

## Add support for C++20

Add `set(CMAKE_CXX_STANDARD 20)` to the top level `CMakeLists.txt`.

### Build and Install

```bash
cd soci
cmake -G "Unix Makefiles" -DWITH_BOOST=ON -DWITH_ORACLE=OFF -DWITH_MYSQL=ON ..
make
sudo make install
```

# MySQL cmake support

Use the cmake file from [Kitware](https://gitlab.kitware.com/cmake/community/-/wikis/contrib/modules/FindMySQL).

## Build the App

```bash
mkdri build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```
