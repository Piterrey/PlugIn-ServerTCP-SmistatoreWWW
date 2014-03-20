#ifndef LIST_HPP
#define LIST_HPP

/*Classe in elemento singolo da ereditare per rendere le varie e successive classi fruibili dalla lista*/
class Nodo
{
	private:
		Nodo* _next;	//Maniglia al nodo successivo
	public:
		Nodo();	
		Nodo(Nodo* next);	//Costruttore con maniglia all'elemento successivo
		~Nodo();
		void	set_next(Nodo* next);	//Imposta il riferimento al prossimo elemento
		Nodo*	get_next();	//Restituisce un puntatore al prossimo elemento
};

class Iterator;	//Dichiaro la presenza di questa classe poichè viene utilizzata in lista

/*Classe che permette la gestione di array dinamici se ereditano "Nodo"*/
class Lista
{
	private:
		Nodo* _last;	//Maniglia all'ultimo elemento indicato
		void remove_Nodo(Nodo* curr);	//Funzione per l'eliminazione dell'intera lista
	public:
		Lista();	
		Lista(Nodo* last);	//Costruttore con primo elemento oppure clonatore di Lista
		~Lista();
		Nodo* add_Nodo(Nodo* add);	//Aggiunge un nuovo elemento all'array ponendolo come primo della lista
		Iterator* create_Iterator();	//Crea un elemento che permette di scanagliare la lista
		Nodo* get_last();	//Restituisce l'ultimo elemento aggiunto
};

/*Classe che permette il movimento e la selezione di elementi all'interno di una Lista*/
class Iterator
{
	private:
		Lista* _lista;	//Maniglia alla lista d'esecuzione
		Nodo* _current;	//Puntatore all'elemento corrente
	public:
		Iterator(Lista* lista);	//Puntatore alla lista da scandagliare
		~Iterator();

		Nodo* get_current();	//Restituisce l'elemento corrente
		Nodo* move_next();	//L'iteratore si muove sull'elemento successivo
		Nodo* move_first();	//Raggiunge il primo elemento della lista
		bool is_done();	//Conferma se si è arrivati o meno alla fine
};



/*#################################### IMPLEMENTAZIONE ####################################*/
/*######################################### Nodo ##########################################*/

	Nodo::Nodo():Nodo(NULL){}	//Mette il puntatire interno a NULL

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

	void Lista::remove_Nodo(Nodo* curr) {	//Elimina ricorsivamente dal primo all'ultimo
		if(curr){	//Se attuale non posto a NULL
			remove_Nodo(curr->get_next());		//Richiama l'eliminazione del prossimo elemento
			delete(curr);	//Dopo l'eliminazione dei successivi procede con la sua eliminazione
		}
	};

	Lista::Lista(){
		_last = NULL;
	}

	Lista::Lista(Nodo* last){
		add_Nodo(last);
	}

	Lista::~Lista() { remove_Nodo(_last); 	};	//Distruttore richiama la funzione ricorsiva

	Nodo* Lista::add_Nodo(Nodo* add){
		add->set_next(_last);	//Aggiunge gli altri elementi della lista come prossimi
		_last = add;	//Imposta l'elemento come il primo accessibile
	}

	Iterator* Lista::create_Iterator(){
		return (new Iterator(this));	//Crea un iteratore di se stessa
	}

	Nodo* Lista::get_last(){
		return _last;
	}

/*######################################## Iteraror ##########################################*/
	//Le funzioni funzionano al contrario del loro nome: move_next() => move_previus()

	Iterator::Iterator(Lista* lista){
		_lista = lista;	//Esegue una copia del puntatore
		_current=_lista->get_last();	//Imposta l'ultimo elemento inserito come corrente
	}

	Iterator::~Iterator(){}

	Nodo* Iterator::get_current(){
		return _current;
	}

	Nodo* Iterator::move_next(){
		if(_current){	//Se non sono giunto a fine lista
			_current=_current->get_next();	//Imposto come attuale il prossimo elemento
		}
		return get_current();
	}

	Nodo* Iterator::move_first(){
		if(_lista){		//Se posseggo una lista
			_current=_lista->get_last();	//Imposto come attuale il suo ultimo elemento inserito
		}
		return get_current();
	}

	bool Iterator::is_done(){	
		return !(_current->get_next());	//Se il prossimo elemento non è a null restituisco vero
	}

/*#########################################################################################*/

#endif