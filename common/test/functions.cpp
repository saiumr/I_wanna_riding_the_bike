//
// Created by 桂明谦 on 2020/1/5.
//

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "engin/imageEntrepot.hpp"

TEST_CASE("GetFilename"){
    string filename = "./abc/wef/lib/ccx.axx";
    REQUIRE(GetFilename(filename) == "ccx.axx");
    filename = "ccx.axx";
    REQUIRE(GetFilename(filename) == "ccx.axx");
    filename = "~/abc/ccx.axx";
    REQUIRE(GetFilename(filename) == "ccx.axx");
    filename = "../ccx.axx";
    REQUIRE(GetFilename(filename) == "ccx.axx");
}

TEST_CASE("GetFilenameWithoutSuffix"){
    string filename = "./abc/wef/lib/ccx.axx";
    REQUIRE(GetFilenameWithoutSuffix(filename)=="ccx");
    filename = "ccx.axx";
    REQUIRE(GetFilenameWithoutSuffix(filename)=="ccx");
    filename = "~/abc/ccx.axx";
    REQUIRE(GetFilenameWithoutSuffix(filename)=="ccx");
    filename = "../ccx.axx";
    REQUIRE(GetFilenameWithoutSuffix(filename)=="ccx");
}

TEST_CASE("GetFileType"){
    string filename = "./abc/wef/lib/xxx.png";
    REQUIRE(GetFileType(filename)==FILE_TYPE_IMAGE);
    filename = "xxx.PNG";
    REQUIRE(GetFileType(filename)==FILE_TYPE_IMAGE);
    filename = "~/cxz/xxx.gif";
    REQUIRE(GetFileType(filename)==FILE_TYPE_IMAGE);
    filename = "~/DOcument/program/abc.Json";
    REQUIRE(GetFileType(filename)==FILE_TYPE_JSON);
    filename = "../abc/vvv.TXT";
    REQUIRE(GetFileType(filename)==FILE_TYPE_TXT);
    filename = "../asdv";
    REQUIRE(GetFileType(filename)==FILE_TYPE_UNRECOGNIZE);
}

TEST_CASE("GetBaseName"){
    string filename = "./abc/wef/lib/xxx.png";
    REQUIRE(GetBaseName(filename)=="./abc/wef/lib");
    filename = "xxx.PNG";
    REQUIRE(GetBaseName(filename)=="");
    filename = "~/cxz/xxx.gif";
    REQUIRE(GetBaseName(filename)=="~/cxz");
    filename = "~/DOcument/program/abc.Json";
    REQUIRE(GetBaseName(filename)=="~/DOcument/program");
    filename = "../abc/vvv.TXT";
    REQUIRE(GetBaseName(filename)=="../abc");
    filename = "../asdv";
    REQUIRE(GetBaseName(filename)=="..");
}
