#include "i2c-mock.h"
#include <cstring>

ssize_t I2CMock::write(const void* buffer, size_t size) const {
    return size;
}

ssize_t I2CMock::read(void* buffer, size_t size) const {
    if (mock_data_.size() < size) {
        throw std::runtime_error("Not enough mock data for I2C read.");
    }

    memcpy(buffer, mock_data_.data(), size);
    mock_data_.erase(mock_data_.begin(), mock_data_.begin() + size);
    return size;
}

void I2CMock::write_reg(uint8_t reg) const {
    // Do nothing in mock
}

void I2CMock::set_next_read_data(const std::vector<uint8_t>& data) {
    mock_data_ = data;
}
