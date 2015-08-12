#ifndef SMW_MAP_LOADER_H
#define SMW_MAP_LOADER_H

#include <cstdio>

class CMap;
enum ReadType: unsigned char;

class MapLoader {
public:
    MapLoader() {}
    virtual ~MapLoader() {}

    virtual bool load(CMap&, FILE* /*, const char**/, ReadType) = 0;
};

class MapLoader1700 : public MapLoader {
public:
    MapLoader1700() : MapLoader() {}
    virtual ~MapLoader1700() {}
    virtual bool load(CMap&, FILE* /*, const char**/, ReadType);

protected:
    virtual void read_autofilters(CMap& map, FILE* mapfile); // compat: autofilters disabled
    virtual void read_mapdata(CMap&, FILE*); // one-tileset mapdata
    virtual void read_background(CMap&, FILE*); // background by ID
    virtual void set_preview_switches(CMap&, FILE*); // compat: switches disabled
    virtual void read_eyecandy(CMap&, FILE*); // simple eyecandy support
    virtual void read_music_category(CMap&, FILE*); // compat: music guessed by background
    virtual void read_warp_locations(CMap&, FILE*);
    virtual void read_warp_exits(CMap&, FILE*);
    virtual bool read_spawn_areas(CMap&, FILE*);
    virtual bool read_draw_areas(CMap& map, FILE* mapfile);
    virtual void read_switches(CMap&, FILE*); // switches stored inverted
};

class MapLoader1701 : public MapLoader1700 {
public:
    MapLoader1701() : MapLoader1700() {}
    virtual ~MapLoader1701() {}

protected:
    virtual void read_background(CMap&, FILE*); // background by underscore-conversion
    virtual void read_music_category(CMap&, FILE*); // music by category ID
};

class MapLoader1702 : public MapLoader1701 {
public:
    MapLoader1702() : MapLoader1701() {}
    virtual ~MapLoader1702() {}

protected:
    virtual void read_autofilters(CMap& map, FILE* mapfile); // 9 autofilter support
    virtual void read_background(CMap&, FILE*); // background as string
};

class MapLoader1800 : public MapLoader1702 {
public:
    MapLoader1800() : MapLoader1702() {}
    virtual ~MapLoader1800() {}
    virtual bool load(CMap&, FILE* /*, const char**/, ReadType);

protected:
    virtual void read_autofilters(CMap& map, FILE* mapfile); // 13 autofilters
    virtual void read_tileset(FILE*); // custom tileset support
    virtual void read_mapdata(CMap&, FILE*); // multi-tileset mapdata
    virtual void read_switches(CMap&, FILE*); // switches stored as-is
    virtual void read_items(CMap&, FILE*); // map item support
    virtual void read_hazards(CMap&, FILE*); // map hazard support
    virtual void read_warp_locations(CMap&, FILE*);
    virtual void read_switchable_blocks(CMap&, FILE*);
    virtual bool read_spawn_areas(CMap&, FILE*);
    virtual void read_extra_tiledata(CMap&, FILE*);
    virtual void read_gamemode_settings(CMap&, FILE*);

private:
    short iMaxTilesetID;
    short* translationid;
    short* tilesetwidths;
    short* tilesetheights;
};

class MapLoader1802 : public MapLoader1800 {
public:
    MapLoader1802() : MapLoader1800() {}
    virtual ~MapLoader1802() {}

protected:
    virtual void read_eyecandy(CMap&, FILE*); // 3-layer eyecandy support
};

#endif // SMW_MAP_LOADER_H
