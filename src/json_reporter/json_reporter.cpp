#include "json_reporter.hpp"
#include <unistd.h>
#include <pwd.h>

JsonReporter::JsonReporter() : server_(json_) {
    report_file_ = getpwuid(getuid())->pw_dir;
}

void JsonReporter::saveReport() {
    
}
