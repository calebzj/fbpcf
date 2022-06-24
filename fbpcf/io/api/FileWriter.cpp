/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "fbpcf/io/api/FileWriter.h"
#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include "fbpcf/io/api/CloudFileWriter.h"
#include "fbpcf/io/api/IOUtils.h"
#include "fbpcf/io/api/LocalFileWriter.h"

namespace fbpcf::io {
FileWriter::FileWriter(std::string filePath) {
  if (IOUtils::isCloudFile(filePath)) {
    childWriter_ = std::make_unique<CloudFileWriter>(filePath);
  } else {
    childWriter_ = std::make_unique<LocalFileWriter>(filePath);
  }
}

FileWriter::~FileWriter() {
  close();
}

size_t FileWriter::write(std::vector<char>& buf) {
  return childWriter_->write(buf);
}

int FileWriter::close() {
  return childWriter_->close();
}
} // namespace fbpcf::io
