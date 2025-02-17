-- ======================================================================================
-- =     CHUNK SYSTEM ON MULTIPLAYER GAME PROTOTYPE SQL SCRIPT TO CREATE DATABASE       =
-- ======================================================================================

CREATE TABLE Players(
 Player_ID INT NOT NULL PRIMARY KEY AUTO_INCREMENT, -- player id
 Username  Varchar(50),                             -- name to identify a player
 p_skin    Varchar(50),                             -- player skin url for download
 PosX INT NOT NULL,                                 -- position on X axis for player
 PosY INT NOT NULL,                                 -- 
 PosZ INT NOT NULL,
 RotP INT NOT NULL
);

CREATE TABLE Modifications(
 Chunk_ID INT NOT NULL PRIMARY KEY AUTO_INCREMENT, -- chunk id
 Chunk_D  INT NOT NULL,                            -- chunk dimension for world expansion
 Chunk_X  INT NOT NULL,                            -- chunk position on z axis
 Chunk_Y  INT NOT NULL,                            -- chunk position on y axis
 Modif_X  INT NOT NULL,                            -- x coordinate of modification
 Modif_Y  INT NOT NULL,                            -- y coordinate of modification
 Modif_Z  INT NOT NULL,                            -- z coordinate of modification
 Player_ID INT NOT NULL                            -- player who did the modification for chunk
);
