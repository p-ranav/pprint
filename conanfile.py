from conans import ConanFile

class PprintConan(ConanFile):
    name = "pprint"
    version = "0.9.2"
    exports_sources = "include/pprint.hpp"
    no_copy_source = True

    def package(self):
        self.copy("pprint.hpp")
