// This file was generated automatically by marshalgen.

#ifndef MarshaledLYSOHit_H
#define MarshaledLYSOHit_H


#include "LYSOHit.hh"
//MSH_include_begin
#include "MarshaledG4String.h"
//MSH_include_end

#include <stdio.h>
#include <string.h>
#include "MarshaledObj.h"

  class MarshaledLYSOHit;

  class ShadowedMarshaledLYSOHit : public LYSOHit{
    friend class MarshaledLYSOHit;
};

  class MarshaledLYSOHit : public MarshaledObj {
public:
    LYSOHit* param;
    ShadowedMarshaledLYSOHit* Shadowed_param;
public:


// Function implementations

MarshaledLYSOHit(LYSOHit* objptr) : MarshaledObj() {
    msh_isUnmarshalDone = false;
    this->param = objptr;
    this->Shadowed_param = (ShadowedMarshaledLYSOHit*)this->param;
    if (objptr == NULL)
        return;

}

MarshaledLYSOHit(void *buf, char isUnmarshaling = 'u')
: MarshaledObj(buf, isUnmarshaling) {
    msh_isUnmarshalDone = false;
}

~MarshaledLYSOHit() {
    //if(msh_isUnmarshalDone && this->param != NULL) {
        //delete this->param;
    //}
}

LYSOHit* unmarshal() {
    //We don't want to unmarshal the buffer is empty.
    if(msh_size <= MSH_HEADER_SIZE) {
        //This is buggy, we can't always assume that
        //obj == NULL <==> List is empty.
        return NULL;
    } else {
        {
	param = new LYSOHit();
	}
        this->Shadowed_param = (ShadowedMarshaledLYSOHit*)this->param;
        this->msh_isUnmarshalDone = true;
        return this->param;
    }
}

void unmarshalTo(LYSOHit* obj) {
    //We don't want to unmarshal the buffer is empty.
    if(msh_size <= MSH_HEADER_SIZE) {
        //This is buggy, we can't always assume that
        //obj == NULL <==> List is empty.
        return;
    } else {
        this->param = obj;
        this->Shadowed_param = (ShadowedMarshaledLYSOHit*)this->param;
        this->msh_isUnmarshalDone = true;
    }
}

};
#endif

