
// =========================================== Physics

void updateBullets(){

    for(int i=0; i<NUMBULLETS; i++){
        bullets[i].updatePosition();
    }
}


void reloadGun(){

    if( bulletsLeft && bulletsInGun < 5 ){

        int loadingReq = 1; //int loadingReq = CLIPSIZE - bulletsInGun;

        if(bulletsLeft >= loadingReq){
            bulletsInGun += loadingReq;
            bulletsLeft -= loadingReq;
        }
        else{
            bulletsInGun += bulletsLeft;
            bulletsLeft = 0;
        }

        sounds.playReloadSound();

    }
    else{
        //play sound of loaded gun
        sounds.playCannotReloadSound();
    }
}

int checkTargetCollisions(float x, float y, float z, float dx, float dy, float dz){

    for(int i=0; i<(int)targets.size(); i++){

        //if there's a collision inside this target's outer bounding box check the ones inside
        if( targets[i].checkCollision(x, y, z, dx, dy, dz) != -1 ){

            std::cout << " Acertei na OUTER BB do alvo " << i << "\n";

            int jMax = targets[i].numBoundingBoxes;
            float distance;

            for(int j=0; j<jMax; j++){

                distance = targets[i].boundingBoxes[j].checkCollision(x, y, z, dx, dy, dz);

                if( distance != -1 ){
                    std::cout << " Acertei na BB " << j << " do alvo " << i << "\n";
                    numTargetsHit++;
                    targets.erase( targets.begin()+ i ); // remove this target
                    bullets[bulletIndex].isActive = false;
                    return j; // stop the bullet in mid-flight

                }

            }

        }
    }

    return -1;

}

int checkExtraCollisions(float x, float y, float z, float dx, float dy, float dz){

    for(int i=0; i<(int)extras.size(); i++){

        //if there's a collision inside this target's outer bounding box check the ones inside
        if( extras[i].checkCollision(x, y, z, dx, dy, dz) != -1 ){

            std::cout << " Acertei na OUTER BB do extra " << i << "\n";

            int jMax = extras[i].numBoundingBoxes;
            float distance;

            for(int j=0; j<jMax; j++){

               distance = extras[i].boundingBoxes[j].checkCollision(x, y, z, dx, dy, dz);

               if( distance != -1 ){
                   std::cout << " Acertei na BB " << j << " do extra " << i << "\n";
                   numExtrasHit++;
                   extras.erase( extras.begin()+ i ); // remove this target
                   return 1; // stop the bullet in mid-flight

               }

            }
        }
    }

    return -1;
}

void shootGun(){

    if(bulletsInGun){

        bulletsInGun--;

        float x, y, z;
        float dx, dy, dz;
        camera.GetDirectionVector(dx, dy, dz); // bullet direction
        camera.GetPos(x, y, z); // initial position

        bullets[bulletIndex].Init(x, y, z, dx, dy, dz, bulletSpeed, 0, 0, 0, true);

        bulletIndex++;

        int targetBBIndex = checkTargetCollisions(x, y, z, dx, dy, dz);

        if( targetBBIndex != -1){
            score += targetValues[targetBBIndex];
        }
        else{
            if( checkExtraCollisions(x, y, z, dx, dy, dz) != -1){
                score += extraValue;
            }
        }

        sounds.playGunFiringSound();

    }
}
