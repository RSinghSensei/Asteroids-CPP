#include "Bullet.h"



Bullet::Bullet(const glm::vec3 playerpos, const GLfloat angle) {
	this->bulpos = playerpos;
	this->bulposog = playerpos;
	this->bulangle = angle;
}

void Bullet::BulletDraw(GLuint& VAO, Shader ref, GLuint& t1, GLfloat dt) {
	glBindVertexArray(VAO); 

	glm::mat4 model(1.0f);

	model = glm::translate(model, this->bulpos);
	model = glm::scale(model, this->Bulletsize);

	this->bulpos.y += this->BulletSpeed * dt *  cos(bulangle);	
	this->bulpos.x += this->BulletSpeed * dt * -sin(bulangle);


	ref.setUniform(t1, "Transform", model);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}


void Bullet::BulletCollision(std::vector<Asteroids*>& astcheck) {
	bool x;
	for (int i = 0; i < astcheck.size(); i++) {
		/*if (astcheck[i]->astpos.x <= this->bulpos.x && this->bulpos.x <= astcheck[i]->astpos.x + astcheck[i]->astsize.x &&
			astcheck[i]->astpos.y <= this->bulpos.y && this->bulpos.y <= astcheck[i]->astpos.y + astcheck[i]->astsize.y)*/
		if(astcheck[i]->astpos.x - (astcheck[i]->astsize.x/2) < this->bulpos.x + (this->Bulletsize.x/2) &&
		   astcheck[i]->astpos.x + (astcheck[i]->astsize.x/2) > this->bulpos.x - (this->Bulletsize.x/2) &&
			astcheck[i]->astpos.y - (astcheck[i]->astsize.y/2) < this->bulpos.y + (this->Bulletsize.y/2) &&
			astcheck[i]->astpos.y + (astcheck[i]->astsize.y/2) > this->bulpos.y - (this->Bulletsize.y/2))						
		{
			std::cout << "Bullet ast collision" << std::endl;
			astcheck[i]->VertexPos();
			Impact = true;
			if (astcheck[i]->astsize.x > 50.0f) {
				Asteroids *tempast = new Asteroids;
				Asteroids* tempast1 = new Asteroids;

				//Setting properties for tempast and debug log
				tempast->astpos  = astcheck[i]->astpos;
				tempast->astsize = astcheck[i]->astsize;
				std::cout << "Pre: " << tempast->astsize.x << " " << tempast->astsize.y << std::endl;
				tempast->astsize.x /= 2.0f;
				tempast->astsize.y /= 2.0f;
				astcheck.push_back(tempast);
				std::cout << "Post: " << tempast->astsize.x << " " << tempast->astsize.y << std::endl;

				//Setting properties for tempast1 and debug log
				tempast1->astpos = astcheck[i]->astpos;
				tempast1->astsize = astcheck[i]->astsize;
				std::cout << "Pre: " << tempast1->astsize.x << " " << tempast1->astsize.y << std::endl;
				tempast1->astsize.x /= 2.0f;
				tempast1->astsize.y /= 2.0f;
				astcheck.push_back(tempast1);
				std::cout << "Post: " << tempast1->astsize.x << " " << tempast1->astsize.y << std::endl;
			
				
			}
			delete astcheck[i];
			astcheck.erase(astcheck.begin() + i);
		}


		/*if (this->bulpos.x < astcheck[i]->astpos.x + astcheck[i]->astsize.x && astcheck[i]->astpos.x < this->bulpos.x + this->Bulletsize.x){}
		if (this->bulpos.x < astcheck[i]->astpos.x + astcheck[i]->astsize.x && astcheck[i]->astpos.x < this->bulpos.x + this->Bulletsize.x){}*/
		
		//if (xcol && ycol) { std::cout << "Bullet Ast collision" << std::endl; }
	}
}

		/*bool xcol, ycol;
		xcol = this->bulpos.x) + this->Bulletsize.x) >= astcheck.astpos.x) && astcheck.astpos.x) + astcheck.astsize.x) >= this->bulpos.x);
		ycol = this->bulpos.y) + this->Bulletsize.y) >= astcheck.astpos.y) && astcheck.astpos.y) + astcheck.astsize.y) >= this->bulpos.y);
		if (xcol && ycol) { std::cout << "Bullet Ast collision" << std::endl; }*/

//this->bulpos.x < astcheck[i]->astpos.x + astcheck[i]->astsize.x &&
//	this->bulpos.x + this->Bulletsize.x > astcheck[i]->astpos.x&&
//	this->bulpos.y < astcheck[i]->astpos.y + astcheck[i]->astsize.y &&
//	this->bulpos.y + this->Bulletsize.y > astcheck[i]->astpos.y