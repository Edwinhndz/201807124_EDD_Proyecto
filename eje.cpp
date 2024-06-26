NodoPiloto* ArbolBB::FindMax(NodoPiloto* root){
	while(root->derecha != NULL) {
        root = root->derecha;
    }
    return root;
}

int ArbolBB::GetHorasByID(const std::string& numero_de_id){
    return GetHorasByID(root, numero_de_id);
}

int ArbolBB::GetHorasByID(NodoPiloto* root, const std::string& numero_de_id) {
    if (root == nullptr) {
        return -1; // Árbol vacío o llegamos a una hoja, retorna -1 como indicador de no encontrado
    }

    // Busca en el subárbol izquierdo
    int leftResult = GetHorasByID(root->izquierda, numero_de_id);
    if (leftResult != -1) {
        return leftResult;
    }

    // Verifica el nodo actual
    if (root->numero_de_id == numero_de_id) {
        return root->horas_de_vuelo;
    }

    // Busca en el subárbol derecho
    return GetHorasByID(root->derecha, numero_de_id);
}


void ArbolBB::EliminarNodo(const std::string& numero_de_id) {
    int horas_de_vuelo = ArbolBB::GetHorasByID(numero_de_id);
    cout << horas_de_vuelo << endl;
    root = BorrarNodo(root, horas_de_vuelo);
}

NodoPiloto* ArbolBB::BorrarNodo(NodoPiloto* root, int horas_de_vuelo) {
	if(root == NULL){
    return root;
    } else if(horas_de_vuelo < root->horas_de_vuelo){
        root->izquierda = BorrarNodo(root->izquierda,horas_de_vuelo);
    }else if (horas_de_vuelo > root->horas_de_vuelo) {
        root->derecha = BorrarNodo(root->derecha,horas_de_vuelo);
    }
	// Wohoo... I found you, Get ready to be deleted	
	else {
		// Case 1:  No child
		if(root->izquierda == NULL && root->derecha == NULL) { 
			delete root;
			root = NULL;
		}
		//Case 2: One child 
		else if(root->izquierda == NULL) {
			NodoPiloto *temp = root;
			root = root->derecha;
			delete temp;
		}
		else if(root->derecha == NULL) {
			NodoPiloto *temp = root;
			root = root->izquierda;
			delete temp;
		}
		// case 3: 2 children
		else { 
			NodoPiloto* temp = FindMax(root->izquierda);
            // Copiamos todos los atributos relevantes
            root->horas_de_vuelo = temp->horas_de_vuelo;
            root->numero_de_id = temp->numero_de_id;
            root->nombre = temp->nombre;
            root->nacionalidad = temp->nacionalidad;
            root->vuelo = temp->vuelo;
            root->tipo_de_licencia = temp->tipo_de_licencia;
            // Eliminar el nodo duplicado en el subárbol izquierdo
            root->izquierda = BorrarNodo(root->izquierda, temp->horas_de_vuelo);
		}
	}
	return root;
}