#include <catch2/catch_test_macros.hpp>

#include "CmdlineParser.hh"
#include "Options.hh"

TEST_CASE("minimum filesize is 1 by default")
{
  Options defaults;
  REQUIRE(defaults.minimumfilesize == 1);
}

TEST_CASE("-ignoreempty false")
{
  const int argc = 3;
  const char* argv[argc] = { "progname", "-ignoreempty", "false" };
  Parser parser(argc, argv);

  Options o = parseOptions(parser);
  REQUIRE(o.minimumfilesize == 0);
}

TEST_CASE("-ignoreempty true")
{
  const int argc = 3;
  const char* argv[argc] = { "progname", "-ignoreempty", "true" };
  Parser parser(argc, argv);

  Options o = parseOptions(parser);
  REQUIRE(o.minimumfilesize == 1);
}

TEST_CASE("-minsize 1234")
{
  const int argc = 3;
  const char* argv[argc] = { "progname", "-minsize", "1234" };
  Parser parser(argc, argv);

  Options o = parseOptions(parser);
  REQUIRE(o.minimumfilesize == 1234);
}

// https://github.com/pauldreik/rdfind/issues/60
TEST_CASE("-minsize 100000000 -ignoreempty true")
{
  const int argc = 5;
  const char* argv[argc] = {
    "progname", "-minsize", "100000000", "-ignoreempty", "true"
  };
  Parser parser(argc, argv);

  Options o = parseOptions(parser);
  REQUIRE(o.minimumfilesize == 100000000);
}

TEST_CASE("-ignoreempty true -minsize 100000000")
{
  const int argc = 5;
  const char* argv[argc] = {
    "progname", "-ignoreempty", "true", "-minsize", "100000000"
  };
  Parser parser(argc, argv);

  Options o = parseOptions(parser);
  REQUIRE(o.minimumfilesize == 100000000);
}

TEST_CASE("-ignoreempty false -minsize 1234")
{
  const int argc = 5;
  const char* argv[argc] = {
    "progname", "-ignoreempty", "false", "-minsize", "1234"
  };
  Parser parser(argc, argv);

  Options o = parseOptions(parser);
  REQUIRE(o.minimumfilesize == 1234);
}

TEST_CASE("-minsize 1234 -ignoreempty false")
{
  const int argc = 5;
  const char* argv[argc] = {
    "progname", "-minsize", "1234", "-ignoreempty", "false"
  };
  Parser parser(argc, argv);

  Options o = parseOptions(parser);
  REQUIRE(o.minimumfilesize == 0);
}
