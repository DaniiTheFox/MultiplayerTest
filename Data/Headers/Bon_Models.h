void draw_square(float scale, GLuint tex){
    glBindTexture(GL_TEXTURE_2D,tex);
    glBegin(GL_QUADS);
     glTexCoord2f(0,0);
     glVertex2f(scale,scale);
     glTexCoord2f(0,1);
     glVertex2f(scale,-scale);
     glTexCoord2f(1,1);
     glVertex2f(-scale,-scale);
     glTexCoord2f(1,0);
     glVertex2f(-scale,scale);
    glEnd();
}

