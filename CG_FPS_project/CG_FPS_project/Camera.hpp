#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>


//------------------------------------------------------------ Observador
const float g_translation_speed = 5;//2.5;
const float g_rotation_speed = M_PI/180* 0.5;
const float limit = 85.0 * M_PI / 180.0;

class Camera{

    public:

        Camera(){}
        ~Camera(){}

        void Refresh(){

            // https://developer.valvesoftware.com/w/images/7/7e/Roll_pitch_yaw.gif
            // Camera parameters according to x/y for flat, z for height
            // For that coord. system: pich = rotation along yy, yaw = rotation along zz

            m_lx = cos(m_yaw) * cos(m_pitch);
            m_ly = sin(m_pitch);
            m_lz = sin(m_yaw) * cos(m_pitch);

            m_strafe_lx = cos(m_yaw - M_PI_2);
            m_strafe_lz = sin(m_yaw - M_PI_2);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(m_x, m_y, m_z, m_x + m_lx, m_y + m_ly, m_z + m_lz, 0.0,1.0,0.0);

        }

        void SetPos(float x, float y, float z){
            m_x = x;
            m_y = y;
            m_z = z;

            Refresh();
        }

        void GetPos(float &x, float &y, float &z){
            x = m_x;
            y = m_y;
            z = m_z;
        }

        void GetDirectionVector(float &x, float &y, float &z){
            x = m_lx;
            y = m_ly;
            z = m_lz;
        }

        // navigation
        void Move(float incr){
            float lx = cos(m_yaw)*cos(m_pitch);
            //float ly = sin(m_pitch); // we don't move vertically
            float lz = sin(m_yaw)*cos(m_pitch);

            m_x = m_x + incr*lx;
            //m_y = m_y + incr*ly; // we don't move vertically
            m_z = m_z + incr*lz;

            Refresh();
        }

        void Strafe(float incr){
            m_x = m_x + incr*m_strafe_lx;
            m_z = m_z + incr*m_strafe_lz;

            Refresh();
        }

        void Fly(float incr){
            m_y = m_y + incr;

            Refresh();
        }

        void RotateYaw(float angle){
            m_yaw += angle;

            Refresh();
        }

        void RotatePitch(float angle){

            m_pitch += angle;

            if(m_pitch < -limit)
                m_pitch = -limit;

            if(m_pitch > limit)
                m_pitch = limit;

            Refresh();
        }

        void SetYaw(float angle){
            m_yaw = angle;

            Refresh();
        }

        void SetPitch(float angle){
            m_pitch = angle;

            Refresh();
        }

    private:
        float m_x, m_y, m_z;   // Position
        float m_lx, m_ly, m_lz; // Direction vector of where we are looking at
        float m_yaw, m_pitch; // Various rotation angles
        float m_strafe_lx, m_strafe_lz; // Always 90 degree to direction vector



};


#endif
