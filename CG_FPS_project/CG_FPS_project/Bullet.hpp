class Bullet{
    public:
        float x, y, z, angle;
        int targetX, targetY, targetZ;
        bool isActive;

        Bullet(){
            isActive = true;
        }
        ~Bullet(){}

        void draw(){

            glPushMatrix();
                glRotatef(angle, 0, 0.5, 1);
                glTranslatef( x, y, z);
                glColor3f (0.4, 0.4, 1);
                glutWireCube(2);
            glPopMatrix();

        }
        bool deleteBullet(){
            if( x == targetX && y == targetY && z == targetZ )
                return true;

            //TODO: update coords for next iteration using angle
            z--;

            return false;
        }
};
