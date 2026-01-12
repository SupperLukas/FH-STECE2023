#pragma once
#include "i2c-interface.h"
#include <vector>
#include <stdexcept>

class I2CMock : public I2CInterface {
public:
    I2CMock() = default;
    ssize_t write(const void* buffer, size_t size) const override;
    ssize_t read(void* buffer, size_t size) const override;
    void write_reg(uint8_t reg) const override;
    void set_next_read_data(const std::vector<uint8_t>& data);

private:
    mutable std::vector<uint8_t> mock_data_;
};
