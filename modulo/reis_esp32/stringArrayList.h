
#ifndef VARIABLES_SAL // header guards
#define VARIABLES_SAL

#define MAX_ARRAY_LIST_SIZE 21
#define MAX_STR_SIZE        4000

class stringArrayList{
  
  private:
  char **list;
  int stringSize = MAX_STR_SIZE;
  int size=1;
  int maxEntry = MAX_ARRAY_LIST_SIZE;

  char **buffer;

  public:
  stringArrayList(){
    this->list = (char**) calloc(1,sizeof(char*));
    this->list[0]  = (char*) calloc(stringSize,sizeof(char));
    this->size=1;

    // dummy entry
    strncpy(this->list[0], "hello world",stringSize);
  }

  int get_size(){return this->size-1;}
  
  char* get_string(int index){

    if(index+1<size)
    return this->list[index+1];
  }

  void set_string(char* value, int index){
    
    if(index+1<size)
    strcpy(this->list[index+1], value);
  }

  void add_string(char* value){

    if(size<=maxEntry){
      
      this->list = (char**) realloc(this->list, (size+1) * sizeof(char*));
      this->list[size]  = (char*) calloc(stringSize,sizeof(char));

      if(this->list==NULL) Serial.println("null");
  
      strncpy(this->list[size], value,stringSize);
  
      size++;
    }    
  }

  void remove_item(int index){

    if(index+1<size){

      /**/
      this->buffer = (char**) calloc(size,sizeof(char*));
      for(int i=0; i<size; i++){
        
        this->buffer[i]  = (char*) calloc(stringSize,sizeof(char));
        strcpy(buffer[i], this->list[i]);
      }
      /**/

      /**/
      // Novo
      for(int i=0; i<size; i++){
        free(this->list[i]);
      }
      free(this->list);

      this->list = (char**) calloc(size-1,sizeof(char*));
      for(int i=0; i<size-1; i++){
        
        this->list[i]  = (char*) calloc(stringSize,sizeof(char));
      }
      /**/

      /**
      // Velho
      this->list = (char**) realloc(this->list, (size-1) * sizeof(char*));
      if(this->list==NULL) Serial.println("null realloc");
      /**/
  
      /**/
      for(int i=0; i<index+1; i++){
  
        strcpy(this->list[i], buffer[i]);
      }
  
      for(int i=index+1; i<size-1; i++){
  
        strcpy(this->list[i], buffer[i+1]);
      }
      /**/
  
      //this->buffer = (char**) realloc(this->buffer, 0 * sizeof(char*));
      //if(this->buffer==NULL) Serial.println("null buffer realloc");

      for(int i=0; i<size; i++){
        free(this->buffer[i]);
      }
      free(this->buffer);
  
      size--;
    }

  }

  void printList(){

    for(int i=1; i<size; i++){
      Serial.println(this->list[i]);
    }
    Serial.println("size: " + String(this->size));
  }

  // TODO : aprimorar essa função -- usar free() ao invés de realloc
  void frela(){
    this->list = (char**) realloc(this->list, 1 * sizeof(char*));
    this->size=1;
  }

  void concatList(char *result){

    String conc_ = String();

    //result[0] = '\0';

    for(int i=1; i<this->size; i++){
      conc_.concat(this->list[i]);
      //Serial.println(conc_);
    }
     
    strcpy(result,conc_.c_str());

    //Serial.println(result);
  }


};

#endif
