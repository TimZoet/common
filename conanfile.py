import re

from conans import ConanFile
from conans.tools import load
from conan.tools.cmake import CMakeToolchain, CMake
from conan.tools.layout import cmake_layout

def get_version():
    try:
        content = load("modules/common/CMakeLists.txt")
        version = re.search("set\(COMMON_VERSION (\d+\.\d+\.\d+)\)", content).group(1)
        return version.strip()
    except Exception as e:
        return None

class CommonConan(ConanFile):
    name = "common"
    version = get_version()

    # Optional metadata
    license = "<Put the package license here>"
    author = "Tim Zoet"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "<Description of Hello here>"
    topics = ("<Put some tag here>", "<here>", "<and here>")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"fPIC": [True, False]}
    default_options = {"fPIC": True}

    exports_sources = "CMakeLists.txt", "readme.md", "cmake/*", "external/*", "modules/*", "tests/*"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["common"]
