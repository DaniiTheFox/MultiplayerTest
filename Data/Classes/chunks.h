// THE WORLD TYPES INSIDE THE PROYECT
#define   FLAT_WORLD 0 // world mode #1 for flat worlds
#define FLAT_N_TREES 1 // world mode #2 for flar worlds with trees
#define MOUNTAIN_WRL 2 // world mode #3 that uses perlin
int upr_sec_x[3] = {0,1,2}; //   0          1        2
int mid_sec_x[3] = {3,4,5}; // 3 4 5   -- 4 5 3 -- 5 3 4
int lwr_sec_x[3] = {6,7,8}; // array of sectors with their locations used for rebuild and organize the world
bool isDebug = false;
// the node that will be useful to save all chunks
struct chunk{
 int zone_X;                   // The location in X in greater map
 int zone_Y;                   // The location in Y in greater map 
 int chunk_data[16][255][16];  // The cubes located inside the chunk
 int state = 0;                // Numbers between 1-9 to mark it's position
};

class Chunk_gen{               // object that contains tree and chunk data
 public:
  int seed = 50;               // seed for world generation 50 for default
  int w_type = 0;              // 0-Flat  1-Flat_n_trees 2-Mountain_n_trees
   chunk *sector[9];           // pointers for each sector (to identify the locations)
   chunk *aux;
   // 0 1 2
   // 3 4 5 -- where 4 it's center chunk -- if player travels to other chunk that chunk will become center chunk
   // 6 7 8  
  // functions
  Chunk_gen(int _s,int w_type);              // object constructor that generates the first 9 chunks for world and sets up everything
  void Chunk_Create(int p, int zx, int zy);  // function to start generating each chunk (here goes world generation)
  void Chunk_Draw();                         // function to move through the tree and start generating the terrain on renderer
  void Chunk_Correction();                   // function to fix the broken chunks and avoid holes
  void Chunk_Update();                       // function to generate new chunks as players moves
};

Chunk_gen::Chunk_gen(int _s, int w){                 // class constructor that sets up all the world generation
 std::cout<<"generating chunks"<<std::endl;          // just a debug message to find segmentation parts
 seed = _s;                                          // seed for perlin noise or tree generation
 w = w_type;                                         // world mode
 int positions_x[9] = {-1,0,1,-1,0,1,-1, 0, 1};      // locations of the first 9 chunks
 int positions_y[9] = { 1,1,1, 0,0,0,-1,-1,-1};      // locations of the first 9 chunks
 for(int i = 0; i < 9; i++){                         // loop through all pointers
  Chunk_Create( i, positions_x[i], positions_y[i]);  // to generate all main chunks at first and avoid segmentations
 }
 aux = new chunk();                                  // create an auxiliary variable for saving the current chunk to read
}

void Chunk_gen::Chunk_Draw(){                        // function to start drawing the chunks
 //std::cout<<"drawing chunks"<<std::endl;
 //std::cout<<"chunk with data: "<<aux->zone_X<<std::endl;
 for(int i = 0; i < 9; i++){                         // loop through all pointers in order to draw each chunk
  aux = sector[i];
  //std::cout<<"testing chunks"<<std::endl;
   for(int z = 0; z < 16;   z++){                    // loop to read Z axis data of the chunk 
    for(int y = (py-5); y < (py+10); y++){           // loop to read Y axis data adjusted to player's positions to optimize generation
     for(int x = 0; x < 16; x++){                    // loop to read X axis data of the chunk
      //if(py-10 < 0){py=0;}
      switch(aux->chunk_data[x][y][z]){              // test the found information about the chunk
       case 1:                                       // reading the objects
        //std::cout<<"found 1"<<std::endl;
        glPushMatrix();                              // used to move individually an object
        glBindTexture(GL_TEXTURE_2D, GRASS_TEXTURE); // set the grass texture
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;
       case 2:
        //std::cout<<"found 2"<<std::endl;
        glPushMatrix();                              // move this block individually
        glBindTexture(GL_TEXTURE_2D, STONE_TEXTURE); // set stone texture to block
        Bon_draw_cube(aux->chunk_data,x,y,z,x+(aux->zone_X*15),y,z+(aux->zone_Y*15),0.5); // calculate and draw optimized cube with it's position
        glPopMatrix();                                                                    // adjusted to chunk location on greater scale
       break;
      }
     }
    }
   }
   if(isDebug == true){
    std::cout<<"For Node: "<<i<<" locations: x- "<<aux->zone_X<<" y- "<<aux->zone_Y<<std::endl;
   }
 }
 if(isDebug == true){   
  isDebug = false;
 }
}
/*
====================================================================================
= TODO: IMPORTANT FUNCTION TO CREATE A NEW CHUNK NODE AND PUSH IT TO TREE ON CLASS =
====================================================================================
*/
void Chunk_gen::Chunk_Create( int p, int zx, int zy ){ // function to create new node of chunk with data
 //std::cout<<"creating chunks"<<std::endl;
 chunk *newchunk = new chunk();                        // create the new chunk node (starts empty)
 //std::cout<<"chunk created..."<<std::endl;
 newchunk->zone_X = zx;                                // assign a zone for this chunk on Z axis
 newchunk->zone_Y = zy;                                // assign a zone for this chunk on Y axis
 //std::cout<<"zone assigned"<<std::endl;
 if(w_type == 0){                                      // world generation testing mode
 //std::cout<<"type tested..."<<std::endl;
  for(int z = 0; z < 16; z++){                          // this is the world generation
   for(int y = 0; y < 50; y++){                         // as this depends on modes or anything
    for(int x = 0; x < 16; x++){                        // since it's mode 0 generates a flat terrain
     //std::cout<<"generating world data"<<std::endl;   // this part is ment to be the loading chunk data
     if(y < 48){                                        // inside the chunk which means MySQL things go here if world is downloaded
      newchunk->chunk_data[x][y][z] = 2;                // this sets information inside the main array
     }else{
      newchunk->chunk_data[x][y][z] = 1;                // of the chunk data
     }
    }                                                   // TODO: IMPORTANT: you can use structures and perlin noise in here
   }
  }
  for(int f = 51; f < (51+p); f++){
   newchunk->chunk_data[8][f][8] = 1;                   // this is just a random stick on chunks ignore it
  }
  std::cout<<"CHUNK "<<p<<" WAS GENERATED IN LOCATION:"<<" x:"<<newchunk->zone_X<<" y:"<<newchunk->zone_Y<<std::endl;
 }
 std::cout<<"setting state"<<std::endl;                 // debug message to identify the state of chunk
 newchunk->state = p;                                   // set state of chunk
 std::cout<<"pushing chunk"<<std::endl;                 // mention when is the chunk being pushed to list
 sector[p] = newchunk;                                  // push the actual chunk to the tree giving the pointer of the class
}

void Chunk_gen::Chunk_Correction(){
 int locs_X[3] = {-1,0,1};
 int locs_Y[3] = {1,0,-1};
 for(int i = 0; i < 3; i++ ){
  aux = sector[upr_sec_x[i]];
   if(aux->zone_X != (loc_X + locs_X[i])||aux->zone_Y != (loc_Y + locs_Y[0])){
    Chunk_Create(upr_sec_x[i],(loc_X + locs_X[i]),(loc_Y + locs_Y[0]));
   }
  aux = sector[mid_sec_x[i]];
   if(aux->zone_X != (loc_X + locs_X[i])||aux->zone_Y != (loc_Y + locs_Y[1])){
    Chunk_Create(mid_sec_x[i],(loc_X + locs_X[i]),(loc_Y + locs_Y[1]));
   }
  aux = sector[lwr_sec_x[i]];
   if(aux->zone_X != (loc_X + locs_X[i])||aux->zone_Y != (loc_Y + locs_Y[2])){
    Chunk_Create(lwr_sec_x[i],(loc_X + locs_X[i]),(loc_Y + locs_Y[2]));
   }
 }
}
/*
=====================================================================================
= TODO: IMPORTANT: FUNCTION TO UPDATE THE CHUNKS AND GENERATE NEW AS PLAYER WALKS   =
=====================================================================================
*/
int aux1,aux2; int auy1[3], auy2[3];    // auxiliary variables for moving the array and generate new chunks and understand next generation
void Chunk_gen::Chunk_Update(){         // FUNCTION TO GENERATE THE CHUNKS AS PLAYER MOVES ON UPDATES
 bool splitted = false;
 if(px > (opx+8)){          // if player moved on positive x axis
  opx += 15;                                       // update current player position on X of the greater scale
  loc_X++;                                         // update the location of chunk
  Chunk_Create(upr_sec_x[0],loc_X+1,loc_Y+1);      // create 3 new chunks on direction
  Chunk_Create(mid_sec_x[0],loc_X+1,loc_Y);        // these are represening their locations 
  Chunk_Create(lwr_sec_x[0],loc_X+1,loc_Y-1);      // by the use of locs of X and Y
  std::cout<<"new chunk is generated x pos: "<<std::endl; // debug message
  std::cout<<"location of new chunks: "<<loc_X+1<<" "<<loc_X+1<<" "<<loc_X+1<<std::endl;
  std::cout<<"location of new chunks: "<<loc_Y-1<<" "<<loc_Y<<" "<<loc_Y+1<<std::endl;
  aux1 = upr_sec_x[2];aux2 = upr_sec_x[1];         // save one of the sectors into auxiliary variables
  upr_sec_x[2] = upr_sec_x[0];                     // move the current variables of x and switch locations 
  upr_sec_x[1] = aux1;                             // set middle current var
  upr_sec_x[0] = aux2;                             // set lower
                                                   // this process is repeated
  aux1 = mid_sec_x[2];aux2 = mid_sec_x[1];         // for each numer on array of sectors
  mid_sec_x[2] = mid_sec_x[0];                     // to assign next chunk location that will be drawn
  mid_sec_x[1] = aux1;                             // this array tells the pointers where to look at
  mid_sec_x[0] = aux2;                             // and how to organize them
  
  aux1 = lwr_sec_x[2];aux2 = lwr_sec_x[1];         // 
  lwr_sec_x[2] = lwr_sec_x[0];
  lwr_sec_x[1] = aux1;
  lwr_sec_x[0] = aux2;
  splitted = true;
 }
 if(px < (opx-8)){
  opx -= 15;
  loc_X--;
  Chunk_Create(upr_sec_x[2],loc_X-1,loc_Y+1);
  Chunk_Create(mid_sec_x[2],loc_X-1,loc_Y);
  Chunk_Create(lwr_sec_x[2],loc_X-1,loc_Y-1);
  std::cout<<"new chunk is generated x neg: "<<std::endl;
  std::cout<<"location of new chunks: "<<loc_X-1<<" "<<loc_X-1<<" "<<loc_X-1<<std::endl;
  std::cout<<"location of new chunks: "<<loc_Y-1<<" "<<loc_Y<<" "<<loc_Y+1<<std::endl;
  aux1 = upr_sec_x[0];aux2 = upr_sec_x[1];
  upr_sec_x[0] = upr_sec_x[2];
  upr_sec_x[1] = aux1;
  upr_sec_x[2] = aux2;
  
  aux1 = mid_sec_x[0];aux2 = mid_sec_x[1];
  mid_sec_x[0] = mid_sec_x[2];
  mid_sec_x[1] = aux1;
  mid_sec_x[2] = aux2;
  
  aux1 = lwr_sec_x[0];aux2 = lwr_sec_x[1];
  lwr_sec_x[0] = lwr_sec_x[2];
  lwr_sec_x[1] = aux1;
  lwr_sec_x[2] = aux2;
  splitted = true;
 }
 if(pz > (opy+8)){
  opy += 15;
  loc_Y++;
  Chunk_Create(lwr_sec_x[0],loc_X+1,loc_Y+1); // create upper chunk
  Chunk_Create(lwr_sec_x[1],loc_X,  loc_Y+1); // create middle chunk
  Chunk_Create(lwr_sec_x[2],loc_X-1,loc_Y+1); // create lower chunk
  std::cout<<"new chunk is generated y pos: "<<std::endl; // debug comment
  std::cout<<"location of new chunks: "<<loc_X-1<<" "<<loc_X<<" "<<loc_X-1<<std::endl;
  std::cout<<"location of new chunks: "<<loc_Y+1<<" "<<loc_Y+1<<" "<<loc_Y+1<<std::endl;
  auy1[0] = upr_sec_x[0]; auy1[1] = upr_sec_x[1]; auy1[2] = upr_sec_x[2];  // upper section saved on auxiliary 
  auy2[0] = mid_sec_x[0]; auy2[1] = mid_sec_x[1]; auy2[2] = mid_sec_x[2];  // middle section saved on auxiliary
  upr_sec_x[0] = lwr_sec_x[0]; upr_sec_x[1] = lwr_sec_x[1]; upr_sec_x[2] = lwr_sec_x[2]; // replace upper with lower sections
  mid_sec_x[0] = auy1[0]; mid_sec_x[1] = auy1[1]; mid_sec_x[2] = auy1[2];  // replace middle section with upper section
  lwr_sec_x[0] = auy2[0]; lwr_sec_x[1] = auy2[1]; lwr_sec_x[2] = auy2[2];  // replace lower section with middle section
  splitted = true;
 }
 if(pz < (opy-8)){
  opy -= 15;
  loc_Y--;
  Chunk_Create(upr_sec_x[0],loc_X+1,loc_Y-1); // create upper chunk
  Chunk_Create(upr_sec_x[1],loc_X,  loc_Y-1); // create middle chunk
  Chunk_Create(upr_sec_x[2],loc_X-1,loc_Y-1); // create lower chunk
  std::cout<<"new chunk is generated y neg: "<<std::endl; // debug comment
  std::cout<<"location of new chunks: "<<loc_X-1<<" "<<loc_X<<" "<<loc_X+1<<std::endl;
  std::cout<<"location of new chunks: "<<loc_Y-1<<" "<<loc_Y-1<<" "<<loc_Y-1<<std::endl;
  auy1[0] = lwr_sec_x[0]; auy1[1] = lwr_sec_x[1]; auy1[2] = lwr_sec_x[2];  // upper section saved on auxiliary 
  auy2[0] = upr_sec_x[0]; auy2[1] = upr_sec_x[1]; auy2[2] = upr_sec_x[2];  // middle section saved on auxiliary
  upr_sec_x[0] = mid_sec_x[0]; upr_sec_x[1] = mid_sec_x[1]; upr_sec_x[2] = mid_sec_x[2]; // replace upper with lower sections
  mid_sec_x[0] = auy1[0]; mid_sec_x[1] = auy1[1]; mid_sec_x[2] = auy1[2];  // replace middle section with upper section
  lwr_sec_x[0] = auy2[0]; lwr_sec_x[1] = auy2[1]; lwr_sec_x[2] = auy2[2];  // replace lower section with middle section
  splitted = true;
 }
 if(splitted == true){
  std::cout<<"Terrain generated is: ["<<upr_sec_x[0]<<" "<<upr_sec_x[1]<<" "<<upr_sec_x[2]<<"]"<<std::endl;
  std::cout<<"                      ["<<mid_sec_x[0]<<" "<<mid_sec_x[1]<<" "<<mid_sec_x[2]<<"]"<<std::endl;
  std::cout<<"                      ["<<lwr_sec_x[0]<<" "<<lwr_sec_x[1]<<" "<<lwr_sec_x[2]<<"]"<<std::endl;
  std::cout<<"Location of player and chunks is: LocX: "<<loc_X<<" LocY: "<<loc_Y<<std::endl;
  std::cout<<"Location of player current chunk: opx: "<<opx<<" opy:"<<opy<<std::endl;
  splitted = false;
 }
 Chunk_Correction();
}

Chunk_gen Wrl_Sys(0,0);
