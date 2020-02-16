from conans import CMake, ConanFile, tools
import os


class PprintConan(ConanFile):
    name = "pprint"
    description = "Pretty Printer for Modern C++"
    topics = ("pprint", "pretty", "printer", "single-header", "c++17")
    homepage = "https://github.com/p-ranav/pprint"
    url = "https://github.com/p-ranav/pprint"
    license = "MIT"
    exports_sources = "include/**", "test/**", "CMakeLists.txt", "LICENSE", "pprint.pc.in"
    exports = "LICENSE"
    no_copy_source = True
    requires = "catch2/2.11.0"
    settings = "os", "arch", "compiler", "build_type"
    generators = "cmake_find_package"

    def set_version(self):
        import re
        m = re.search(r"project\(.*VERSION ([0-9.]+)", open(os.path.join(self.recipe_folder, "CMakeLists.txt")).read())
        assert m, "Could not extract version from CMakeLists.txt"
        self.version = m.group(1)

    _cmake = None

    def _configure_cmake(self):
        if self._cmake:
            return self._cmake
        self._cmake = CMake(self)
        if tools.get_env("CONAN_RUN_TESTS"):
            self._cmake.definitions["PPRINT_BUILD_TESTS"] = True
        self._cmake.configure()
        return self._cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
        if tools.get_env("CONAN_RUN_TESTS"):
            self._cmake.test()

    def package(self):
        self.copy("LICENSE", dst="licenses")
        cmake = self._configure_cmake()
        cmake.install()

    def package_id(self):
        self.info.header_only()

    def package_info(self):
        self.cpp_info.includedirs.append(os.path.join("include", "pprint"))
