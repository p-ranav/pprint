from conans import CMake, ConanFile
import os


class PprintConan(ConanFile):
    name = "pprint"
    description = "Pretty Printer for Modern C++"
    topics = ("pprint", "pretty", "printer", "single-header", "c++17")
    homepage = "https://github.com/p-ranav/pprint"
    url = "https://github.com/p-ranav/pprint"
    license = "MIT"
    exports_sources = "include/pprint.hpp"
    no_copy_source = True

    _cmake = None

    def _configure_cmake(self):
        if self._cmake:
            return self._cmake
        self._cmake = CMake(self)
        self._cmake.configure()

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        self.copy("LICENSE", dst="licenses")
        cmake = self._configure_cmake()
        cmake.install()

    def package_id(self):
        self.info.header_only()

    def package_info(self):
        self.cpp_info.includedirs.append(os.path.join("include", "pprint"))
