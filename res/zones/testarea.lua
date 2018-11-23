return {
  version = "1.1",
  luaversion = "5.1",
  tiledversion = "0.14.2",
  orientation = "orthogonal",
  renderorder = "right-down",
  width = 12,
  height = 17,
  tilewidth = 32,
  tileheight = 32,
  nextobjectid = 1,
  properties = {},
  tilesets = {
    {
      name = "tiles",
      firstgid = 1,
      tilewidth = 32,
      tileheight = 32,
      spacing = 0,
      margin = 0,
      image = "../tiles.png",
      imagewidth = 320,
      imageheight = 320,
      tileoffset = {
        x = 0,
        y = 0
      },
      properties = {},
      terrains = {},
      tilecount = 100,
      tiles = {}
    }
  },
  layers = {
    {
      type = "tilelayer",
      name = "Tile Layer 1",
      x = 0,
      y = 0,
      width = 12,
      height = 17,
      visible = true,
      opacity = 1,
      offsetx = 0,
      offsety = 0,
      properties = {},
      encoding = "lua",
      data = {
        1, 2, 13, 14, 15, 16, 7, 1, 1, 1, 71, 1,
        1, 2, 13, 14, 15, 16, 7, 1, 1, 1, 1, 1,
        71, 2, 13, 14, 15, 16, 7, 1, 1, 1, 1, 1,
        1, 2, 13, 14, 15, 16, 7, 1, 1, 1, 71, 1,
        1, 2, 13, 14, 15, 16, 7, 71, 1, 1, 1, 1,
        1, 2, 13, 14, 15, 16, 7, 1, 1, 1, 1, 1,
        71, 2, 13, 14, 15, 16, 7, 1, 1, 71, 1, 1,
        1, 2, 13, 14, 15, 16, 7, 1, 1, 1, 1, 1,
        11, 12, 13, 14, 15, 16, 17, 11, 11, 11, 11, 11,
        22, 22, 23, 24, 25, 26, 22, 22, 22, 22, 22, 22,
        32, 32, 33, 34, 35, 36, 32, 32, 32, 32, 32, 32,
        42, 42, 43, 44, 45, 46, 42, 42, 42, 42, 42, 42,
        52, 52, 53, 54, 55, 56, 52, 52, 52, 52, 52, 52,
        61, 62, 13, 14, 15, 16, 67, 61, 61, 61, 61, 61,
        1, 2, 13, 14, 15, 16, 7, 1, 1, 1, 1, 1,
        71, 2, 13, 14, 15, 16, 7, 1, 1, 1, 71, 1,
        1, 2, 13, 14, 15, 16, 7, 71, 1, 1, 1, 1
      }
    }
  }
}
