#pragma once

#ifdef MUZZLE_USE_MODERN_RENDERER

#define mzBegin         rlBegin
#define mzEnd           rlEnd
#define mzVertex2i      rlVertex2i
#define mzVertex2f      rlVertex2f
#define mzVertex3f      rlVertex3f
#define mzTexCoord2f    rlTexCoord2f
#define mzNormal3f      rlNormal3f
#define mzColor4ub      rlColor4ub
#define mzColor3f       rlColor3f
#define mzColor4f       rlColor4f
#define mzPushMatrix    rlPushMatrix
#define mzPopMatrix     rlPopMatrix
#define mzTranslatef    rlTranslatef
#define mzScalef        rlScalef
#define mzRotatef       rlRotatef

#else

#define mzBegin         glBegin
#define mzEnd           glEnd
#define mzVertex2i      glVertex2i
#define mzVertex2f      glVertex2f
#define mzVertex3f      glVertex3f
#define mzTexCoord2f    glTexCoord2f
#define mzNormal3f      glNormal3f
#define mzColor4ub      glColor4ub
#define mzColor3f       glColor3f
#define mzColor4f       glColor4f
#define mzPushMatrix    glPushMatrix
#define mzPopMatrix     glPopMatrix
#define mzTranslatef    glTranslatef
#define mzScalef        glScalef
#define mzRotatef       glRotatef

// bri'sh versions

#define mzColour4ub     mzColor4ub
#define mzColour3f      mzColor3f
#define mzColour4f      mzColor4f

#endif // MUZZLE_USE_MODERN_RENDERER