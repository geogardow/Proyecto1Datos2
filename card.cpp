#include "card.h"
#include <string>
/**
 * @brief Construct a new card::card object
 * 
 * @param i 
 * @param j 
 * @param idPic 
 * @param status 
 */
card::card(int i, int j, int idPic, int status){
    this->i = i;
    this->j = j;
    this->idPic = idPic;
    this->status = status;
}