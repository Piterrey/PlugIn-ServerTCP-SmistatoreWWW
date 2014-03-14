#ifndef LIST_HPP
#define LIST_HPP

class Nodo
{
	private:
		Nodo* _next;
	public:
		Nodo();
		Nodo(Nodo* next);
		~Nodo();
		void	set_next(Nodo* next);
		Nodo*	get_next();
};

class Lista;

class Iterator
{
	private:
		Lista* _lista;
		Nodo* _current;
	public:
		Iterator(Lista* lista);
		~Iterator();

		Nodo* get_current();
		Nodo* move_next();
		Nodo* move_first();
		bool is_done();
};

class Lista
{
	private:
		Nodo* _first;
		void remove_Nodo(Nodo* curr);
	public:
		Lista();
		Lista(Nodo* first);
		~Lista();
		Nodo* add_Nodo(Nodo* add);
		Iterator* create_Iterator();
		Nodo* get_first();
};



/*#################################### IMPLEMENTAZIONE ####################################*/
/*######################################### Nodo ##########################################*/

	Nodo::Nodo():Nodo(NULL){}

	Nodo::Nodo(Nodo* next){
		set_next(next);
	}

	Nodo::~Nodo() {}

	void	Nodo::set_next(Nodo* next){
		_next=next;
	}

	Nodo*	Nodo::get_next(){
		return _next;
	}

/*######################################## Lista ##########################################*/

	void Lista::remove_Nodo(Nodo* curr) {
		if(curr){
			remove_Nodo(curr->get_next());
			delete(curr);
		}
	};

	Lista::Lista(){
		_first=NULL;
	}

	Lista::Lista(Nodo* first){
		add_Nodo(first);
	}

	Lista::~Lista() { remove_Nodo(_first); 	};

	Nodo* Lista::add_Nodo(Nodo* add){
		add->set_next(_first);
		_first = add;
	}

	Iterator* Lista::create_Iterator(){
		return (new Iterator(this));
	}

	Nodo* Lista::get_first(){
		return _first;
	}

/*######################################## Lista ##########################################*/

	Iterator::Iterator(Lista* lista){
		_lista = lista;
		_current=_lista->get_first();
	}

	Iterator::~Iterator(){}

	Nodo* Iterator::get_current(){
		return _current;
	}

	Nodo* Iterator::move_next(){
		if(_current){
			_current=_current->get_next();
		}
		return get_current();
	}

	Nodo* Iterator::move_first(){
		if(_lista){
			_current=_lista->get_first();
		}
		return get_current();
	}

	bool Iterator::is_done(){
		return !(_current->get_next());
	}

/*#########################################################################################*/

#endif