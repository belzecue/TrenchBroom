/*
 Copyright (C) 2010-2017 Kristian Duske

 This file is part of TrenchBroom.

 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "Macros.h"

#include <kdl/reflection_decl.h>

#include <string>
#include <variant>

namespace TrenchBroom
{
namespace Model
{
struct CompilationExportMap
{
  bool enabled;
  std::string targetSpec;

  kdl_reflect_decl(CompilationExportMap, enabled, targetSpec);
};

struct CompilationCopyFiles
{
  bool enabled;
  std::string sourceSpec;
  std::string targetSpec;

  kdl_reflect_decl(CompilationCopyFiles, enabled, sourceSpec, targetSpec);
};

struct CompilationRenameFile
{
  bool enabled;
  std::string sourceSpec;
  std::string targetSpec;

  kdl_reflect_decl(CompilationRenameFile, enabled, sourceSpec, targetSpec);
};

struct CompilationDeleteFiles
{
  bool enabled;
  std::string targetSpec;

  kdl_reflect_decl(CompilationDeleteFiles, enabled, targetSpec);
};

struct CompilationRunTool
{
  bool enabled;
  std::string toolSpec;
  std::string parameterSpec;
  bool treatNonZeroResultCodeAsError;

  kdl_reflect_decl(
    CompilationRunTool, enabled, toolSpec, parameterSpec, treatNonZeroResultCodeAsError);
};

using CompilationTask = std::variant<
  CompilationExportMap,
  CompilationCopyFiles,
  CompilationRenameFile,
  CompilationDeleteFiles,
  CompilationRunTool>;

std::ostream& operator<<(std::ostream& lhs, const CompilationTask& rhs);

} // namespace Model
} // namespace TrenchBroom
