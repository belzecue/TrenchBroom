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

#include "Assets/EntityModel.h"
#include "Assets/Palette.h"
#include "Error.h"
#include "IO/DiskFileSystem.h"
#include "IO/DiskIO.h"
#include "IO/File.h"
#include "IO/MdlParser.h"
#include "IO/Reader.h"
#include "Logger.h"
#include "Model/EntityNode.h"

#include <kdl/result.h>

#include "Catch2.h"

namespace TrenchBroom
{
namespace IO
{
TEST_CASE("MdlParserTest.loadValidMdl")
{
  auto logger = NullLogger{};

  const auto palettePath = "fixture/test/palette.lmp";
  auto fs = DiskFileSystem{std::filesystem::current_path()};
  auto paletteFile = fs.openFile("fixture/test/palette.lmp").value();
  const auto palette = Assets::loadPalette(*paletteFile, palettePath).value();

  const auto mdlPath = std::filesystem::current_path() / "fixture/test/IO/Mdl/armor.mdl";
  const auto mdlFile = Disk::openFile(mdlPath).value();

  auto reader = mdlFile->reader().buffer();
  auto parser = MdlParser("armor", reader, palette);
  auto model = parser.initializeModel(logger);
  parser.loadFrame(0, *model, logger);

  CHECK(model != nullptr);
  CHECK(model->surfaceCount() == 1u);
  CHECK(model->frameCount() == 1u);

  const auto surfaces = model->surfaces();
  const auto& surface = *surfaces.front();
  CHECK(surface.skinCount() == 3u);
  CHECK(surface.frameCount() == 1u);
}

TEST_CASE("MdlParserTest.loadInvalidMdl")
{
  auto logger = NullLogger{};

  const auto palettePath = "fixture/test/palette.lmp";
  auto fs = DiskFileSystem{std::filesystem::current_path()};
  auto paletteFile = fs.openFile("fixture/test/palette.lmp").value();
  const auto palette = Assets::loadPalette(*paletteFile, palettePath).value();

  const auto mdlPath =
    std::filesystem::current_path() / "fixture/test/IO/Mdl/invalid.mdl";
  const auto mdlFile = Disk::openFile(mdlPath).value();

  auto reader = mdlFile->reader().buffer();
  auto parser = MdlParser("armor", reader, palette);
  CHECK_THROWS_AS(parser.initializeModel(logger), AssetException);
}
} // namespace IO
} // namespace TrenchBroom
