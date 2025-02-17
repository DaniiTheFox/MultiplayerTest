// -------------------KEY SCREEN POSITIONS AND SIZE ---------------------
#define BON_SCREEN_W 640         // SCREEN SIZE VARIABLES ON X AXIS
#define BON_SCREEN_H 480         // SCREEN SIZE VARIABLES ON Y AXIS

// --------------- SELF PLAYER POSITION ON GAME -------------------------
float px = 8, py = 51, pz = 8;
float cx = 0, cy = 0, cz = 0;
float angle = 180, angl2 = 0;
int loc_X = 0,loc_Y = 0;
int opx = 8,opy = 8;

// ------------- TEXTURE IDENTIFIERS VARIABLES --------------------------
GLuint GRASS_TEXTURE;
GLuint COBBLESTONE_TEXTURE;
GLuint DIRT_TEXTURE;
GLuint STONE_TEXTURE;
GLuint WATER_TEXTURE;
GLuint SKY_TEXTURE;

// ------------- TEXTURE OFFSET FOR FIXING THE LOAD ----------------------
float xoff = 0.39;
