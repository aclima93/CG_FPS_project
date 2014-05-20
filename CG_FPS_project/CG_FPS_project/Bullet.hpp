class Bullet{
    public:
        float x, y, z, angle;
        int targetX, targetY, targetZ;

        void draw(){
            glPushMatrix();
            glRotatef(angle, 0, 0.5, 1);
            glTranslatef(x, y, z);
            glColor3f (0, 0.2, 1);
            glutWireSphere(5, 10, 10);
            glPopMatrix();
        }
};
