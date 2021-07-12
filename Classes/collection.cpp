#include "collection.h"

Collection::Collection() : list(){
    try {
        std::string s = readFile("data.xml");
        if (s != ""){
            if (s.find("<Data>") != -1 && s.find("</Data>") != -1){
                std::cout<<"Sto leggendo"<<std::endl;
                int i = 0;
                while(s.find("<Item" + std::to_string(i) + '>') != -1)
                {
                    std::string item = Obj::substring(s,"<Item" + std::to_string(i) +'>' ,"</Item" + std::to_string(i) +'>');
                    if (item.find("<Melee>") != -1 && item.find("</Melee>") != -1)
                    {   
                        list.insertBack(DeepPtr<Obj>(new Melee(item)));
                    }
                    else if (item.find("<Ranged>") != -1 && item.find("</Ranged>") != -1)
                    {
                        list.insertBack(DeepPtr<Obj>(new Ranged(item)));
                    }
                    else if (item.find("<Armor>") != -1 && item.find("</Armor>") != -1)
                    {
                        list.insertBack(DeepPtr<Obj>(new Armor(item)));
                    }
                    else if (item.find("<Healing>") != -1 && item.find("</Healing>") != -1)
                    {
                        list.insertBack(DeepPtr<Obj>(new Healing(item)));
                    }
                    else if (item.find("<Buff>") != -1 && item.find("</Buff>") != -1)
                    {
                        list.insertBack(DeepPtr<Obj>(new Buff(item)));
                    }
                    i++;
                }
                std::cout<<"Database letto"<<std::endl;
            }else throw err_file();
        }else throw err_fileNotReadable();
    }
    catch(err_file){std::cout<<"Il database non è corretto"<<std::endl;}
    catch(err_fileNotReadable) {std::cout<<"Il database non esiste"<<std::endl;}
    catch(err_import){std::cout<<"L'importazione non è andata a buon fine"<<std::endl; abort();}
    catch(err_sub){std::cout<<"Substring ha fallito : valori mancanti"<<std::endl; abort();}
    
}

Collection::~Collection(){
    std::cout<<"Cancellazione collection"<<std::endl;
    try{
        save();
    }
    catch(err_fileNotCreated){std::cout<<"Non è stato possibile salvare il database"<<std::endl;}
}

void Collection::save(){
    
    std::cout<<"Sto salvando...";
    std::string s = "<Data>";
    int i = 0;
    for (C<DeepPtr<Obj>>::const_iterator iter = list.begin(); iter != list.end(); ++iter )
    {
        s += "<Item" + std::to_string(i) + '>';
        s += (*iter)->exp();
        s += "</Item" + std::to_string(i) + '>';
        i++;
    }
    s += "</Data>";
    std::ofstream out("data.xml");
    if(out)
    {
        out<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<s;
        out.close();
        std::cout<<"Salvato!"<<std::endl;
    }else throw err_fileNotCreated();
}

int Collection::generateId(){
    int max = -1;
    for (C<DeepPtr<Obj>>::const_iterator i = list.begin(); i != list.end(); ++i)
    {
        if ((*i)->getId()>max)
        {
            max = (*i)->getId();
        }
        
    }
    return max+1;
}

void Collection::add(std::string n, std::string a_t, std::string r, int d_v, int d){
    int id = generateId();
    list.insertBack(DeepPtr<Obj>(new Armor(id, n, a_t, r, d_v, d)));
}

void Collection::add(std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, std::string a_t, std::string a_e, int d){
    int id = generateId();
    list.insertBack(DeepPtr<Obj>(new Melee(id,n,w,c,r,rav,cc,s_str,s_dex,s_aim,a_t,a_e,d)));
}

void Collection::add(std::string n, int w, int c, int r, int rav, int cc, int s_str, int s_dex, int s_aim, int rec, int rel, int m){
    int id = generateId();
    list.insertBack(DeepPtr<Obj>(new Ranged(id,n,w,c,r,rav,cc,s_str,s_dex,s_aim,rec,rel,m)));
}

void Collection::add(std::string n, std::string e, int p, int d){
    int id = generateId();
    list.insertBack(DeepPtr<Obj>(new Buff(id,n,e,p,d)));
}

void Collection::add(std::string n, std::string a_v, int p){
    int id = generateId();
    list.insertBack(DeepPtr<Obj>(new Healing(id,n,a_v,p)));
}

bool Collection::remove(int id){
    C<DeepPtr<Obj>>::const_iterator i = getIter(id);

    if (i != list.end())
    {
        list.remove(*i);
        return true;
    }

    return false;
}

std::string Collection::readFile(std::string filename)          //ritorna tutto il file sottoforma di stringa
{
    std::string file;
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if(in)
    {
        in.seekg(0, std::ios::end);
        file.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&file[0], file.size());
        in.close();
        return file;
    }
    else throw err_fileNotReadable();
}

bool Collection::checkId(const int id) const{
    for (C<DeepPtr<Obj>>::const_iterator i = list.begin(); i != list.end(); ++i )
    {
        if ((*i)->getId() == id)
        {   
            return true;
        }
    }
    return false;
}

C<DeepPtr<Obj>>::const_iterator Collection::getIter(int id) const{
    C<DeepPtr<Obj>>::const_iterator i = list.begin();
    bool found = false;

    while(i!= list.end() && !found)
    {
        if ((*i)->getId() == id)
        {
            found = true;
        }else{
            i++;
        }
    }
    return i;
}



bool Collection::importObj(std::string filename){
    try{
        std::string file = readFile(filename);
        if(file.find("<Id>") != -1 && file.find("</Id>") != -1)
        {
            int probId = stoi(Obj::substring(file, "<Id>", "</Id>"));
            //std::cout<<probId<<std::endl;
            if(!checkId(probId)){

                if (file.find("<Melee>") != -1 && file.find("</Melee>") != -1)
                {   
                    list.insertBack(DeepPtr<Obj>(new Melee(file)));
                }
                else if (file.find("<Ranged>") != -1 && file.find("</Ranged>") != -1)
                {
                    list.insertBack(DeepPtr<Obj>(new Ranged(file)));
                }
                else if (file.find("<Armor>") != -1 && file.find("</Armor>") != -1)
                {
                    list.insertBack(DeepPtr<Obj>(new Armor(file)));
                }
                else if (file.find("<Healing>") != -1 && file.find("</Healing>") != -1)
                {
                    list.insertBack(DeepPtr<Obj>(new Healing(file)));
                }
                else if (file.find("<Buff>") != -1 && file.find("</Buff>") != -1)
                {
                    list.insertBack(DeepPtr<Obj>(new Buff(file)));
                }
                else{
                    throw err_file();
                    return false;
                }
                return true;
                
            }else{
                throw err_notNew();
                return false;
            }
        }else{
            throw err_file();
            return false;
        }
    }
    catch(err_file){std::cout<<"Il file non è corretto"<<std::endl; return false;}
    catch(err_fileNotReadable){std::cout<<"Il file non esiste"<<std::endl;}
    catch(err_import){std::cout<<"Il file non esiste"<<std::endl;}
    catch(err_notNew){std::cout<<"L'oggetto è già presente"<<std::endl; return false;}
    catch(err_sub){std::cout<<"Substring ha fallito : valori mancanti"<<std::endl; abort();}


}

void Collection::exportObj(int id, std::string filename){
    C<DeepPtr<Obj>>::const_iterator i = getIter(id);
    
    try {
        if (i != list.end())
        {
            std::string ex = (*i)->exp();
            std::ofstream out(filename);
            if(out)
            {
                out<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<ex;
                out.close();
            }
            else throw err_fileNotCreated();
        }else throw err_notFound();  
    } 
    catch(err_fileNotCreated){std::cout<<"Il file non è stato creato"<<std::endl;} 
    catch(err_notFound){std::cout<<"L'oggetto da esportare non esiste"<<std::endl;}

}

void Collection::importChara(std::string filename){
    try{
        std::string file = readFile(filename);

        chara = Character(file);

        DeepPtr<Weapon> w = chara.getEqWeap();
        if(!checkId(w->getId()))
        {
            
            if (Melee* m = dynamic_cast<Melee*>(&(*w)))
            {
                list.insertBack(DeepPtr<Obj>(new Melee(*m)));
            }
            else if (Ranged* b = dynamic_cast<Ranged*>(&(*w)))
            {
                list.insertBack(DeepPtr<Obj>(new Ranged(*b)));
            }
        }

        C<DeepPtr<Armor>> a = chara.getEqArmor();
        for (C<DeepPtr<Armor>>::const_iterator i = a.begin(); i != a.end(); ++i)
        {
            if(!checkId((*i)->getId()))
            {
                list.insertBack(DeepPtr<Obj>(new Armor(*(*i))));
            }
        }

        C<DeepPtr<Consumable>> c = chara.getInv();
        for (C<DeepPtr<Consumable>>::const_iterator i = c.begin(); i != c.end(); ++i)
        {
            if(!checkId((*i)->getId()))
            {
                if (Healing* h = dynamic_cast<Healing*>(&(*(*i))))
                {
                    list.insertBack(DeepPtr<Obj>(new Healing(*h)));
                }
                else if (Buff* b = dynamic_cast<Buff*>(&(*(*i))))
                {
                    list.insertBack(DeepPtr<Obj>(new Buff(*b)));
                }
            }
        }
    }
    catch(err_fileNotReadable){std::cout<<"Il file non esiste"<<std::endl; abort();}
    catch(err_import){std::cout<<"L'importazione non è andata a buon fine"<<std::endl; abort();}
    catch(err_sub) {std::cout<<"Substring ha fallito : valori mancanti"<<std::endl; abort();}
    
}

void Collection::exportChara(std::string filename){
    std::string ex = chara.exp();

    try{
        std::ofstream out(filename);
        if (out)
        {
            out<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<ex;
            out.close();
        }
        else throw err_fileNotCreated();
    }
    catch(err_fileNotCreated){std::cout<<"Il file non è stato creato"<<std::endl;}
}

void Collection::show(int id){
    C<DeepPtr<Obj>>::const_iterator i = getIter(id);
    try{
        if (i != list.end())
        {
            std::cout<<*i<<std::endl;
        }
        else{
            throw err_notFound();
        }
    }
    catch(err_notFound){std::cout<<"L'oggetto non esiste"<<std::endl;}

}

void Collection::modifyCharName(std::string s){ chara.setName(s);}

void Collection::modifyCharWeap(int id){
    C<DeepPtr<Obj>>::const_iterator i = getIter(id);
    try {
        chara.setWeap(*i);
    }
    catch(err_wrongType){std::cout<<"L'oggetto è di un tipo non consono"<<std::endl;}
}

void Collection::addCharArmor(int id1, int id2){
    try{
        if (id2 != -1)
        {
            removeCharEq(id2);
        }
        C<DeepPtr<Obj>>::const_iterator i = getIter(id1);
        chara.addArmor(*i);
    }
    catch(err_wrongType){std::cout<<"L'oggetto è di un tipo non consono"<<std::endl;}
    catch(err_notFound){std::cout<<"L'oggetto non esiste"<<std::endl;}
    catch(err_disequip){std::cout<<"L'oggetto non può essere rimosso"<<std::endl;}
}

void Collection::addCharInv(int id1, int id2){
    try{
        if (id2 != -1)
        {
            removeCharEq(id2);
        }
        C<DeepPtr<Obj>>::const_iterator i = getIter(id1);
        chara.addConsum(*i);
    }
    catch(err_wrongType){std::cout<<"L'oggetto è di un tipo non consono"<<std::endl;}
    catch(err_notFound){std::cout<<"L'oggetto non esiste"<<std::endl;}
    catch(err_disequip){std::cout<<"L'oggetto non può essere rimosso"<<std::endl;}
}

void Collection::removeCharEq(int id){
    C<DeepPtr<Obj>>::const_iterator i = getIter(id);
    if ((i != list.end()) && (dynamic_cast<Healing*>(&(*(*i)))  ||  dynamic_cast<Buff*>(&(*(*i))) || dynamic_cast<Armor*>(&(*(*i)))))
    {
        chara.disequip(*i);
    }else throw err_wrongType();
}

void Collection::setCharVit(int x){chara.setVit(x);}
void Collection::setCharStr(int x){chara.setStr(x);}
void Collection::setCharDex(int x){chara.setDex(x);}
void Collection::setCharAim(int x){chara.setAim(x);}


 C<DeepPtr<Obj>> Collection::getObjType(std::string type, std::string type2 ) const{
    C<DeepPtr<Obj>> l;
    for (C<DeepPtr<Obj>>::const_iterator i = list.begin(); i != list.end(); ++i)
    {
        std::cout<< "nel for" << std::endl;
        if (type == "Weapon" && dynamic_cast<Weapon*>(&(*(*i))))    //Ampliabile
        {
            l.insertBack(*i);
        }
        else if (type == "Consumable" && dynamic_cast<Consumable*>(&(*(*i))))   //Ampliabile
        {
            l.insertBack(*i);
        }
        else if (type == "Armor")
        {
            if (Armor* a = dynamic_cast<Armor*>(&(*(*i))))          
            {
                if (a->getArmorType() == type2)
                {
                    l.insertBack(*i);
                }
            }
        }
    }
    return l;
}





