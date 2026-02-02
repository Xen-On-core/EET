#include "dbms_info.hh"

dbms_info::dbms_info(map<string,string>& options)
{
    dbms_name = options["dbms"];

    if (false) {}
    #ifdef HAVE_LIBSQLITE3
    else if (dbms_name == "sqlite") {
        test_port = 0; // no port
        test_db = options["database"];
        can_trigger_error_in_txn = true;
    }
    #endif

    #ifdef HAVE_LIBMYSQLCLIENT
    else if (dbms_name == "tidb") {
        test_port = stoi(options["port"]);
        test_db = options["database"];
        can_trigger_error_in_txn = true;
    }
    else if (dbms_name == "mysql") {
        test_port = stoi(options["port"]);
        test_db = options["database"];
        can_trigger_error_in_txn = true;
    }
    else if (dbms_name == "oceanbase") {
        test_port = stoi(options["port"]);
        test_db = options["database"];
        host_addr = options["host"];
        can_trigger_error_in_txn = true;
    }
    #endif

    else if (dbms_name == "clickhouse") {
        test_port = stoi(options["port"]);
        test_db = options["database"];
        can_trigger_error_in_txn = false;
    }
    else if (dbms_name == "postgres") {
        test_port = stoi(options["port"]);
        test_db = options["database"];
        inst_path = options.count("path") ? options["path"] : "/usr/local/pgsql";
        can_trigger_error_in_txn = false;
    }
    else if (dbms_name == "yugabyte") {
        test_port = stoi(options["port"]);
        test_db = options["database"];
        host_addr = options["host"];
        can_trigger_error_in_txn = false;
    }
    else if (dbms_name == "cockroach") {
        test_port = stoi(options["port"]);
        test_db = options["database"];
        host_addr = options["host"];
        can_trigger_error_in_txn = false;
    }
    else {
        cerr << "Sorry,  you should specify a dbms and its database, or your dbms is not supported, or you miss arguments" << endl;
        throw runtime_error("Does not define target dbms and db in dbms_info::dbms_info()");
    }

    if (options.count("output-or-affect-num"))
        ouput_or_affect_num = stoi(options["output-or-affect-num"]);
    else
        ouput_or_affect_num = 0;

    return;
}