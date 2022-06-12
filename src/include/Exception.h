// Copyright (c)  2022.  Raphael Prandini Thomé de Abrantes
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <iostream>
#include <utility>

class DeviceNotFound : public std::exception {
public:
    explicit DeviceNotFound(const std::string &deviceName) {
        this->deviceName = "Device not found: " +
                           deviceName +
                           "\n\nCheck if controller is connected";
    }

    [[nodiscard]] const char *what() const noexcept override {
        return deviceName.c_str();
    }

private:
    std::string deviceName;
};

class FileNotFound : public std::exception {
public:
    explicit FileNotFound(const std::string &filename) {
        this->fileName = "File not found: " + filename;
    }

    [[nodiscard]] const char *what() const noexcept override {
        return fileName.c_str();
    }

private:
    std::string fileName;
};

class DeviceDisconnected : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Unknown Exception";
    }
};

class UnableToCreateVirtualDevice : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Unable to create the virtual device";
    }
};
