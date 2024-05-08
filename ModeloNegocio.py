import tkinter as tk
from tkinter import ttk
from tkinter import messagebox
import sqlite3

class UsuarioModelo:
    def __init__(self, db_nombre):
        self.conexion = sqlite3.connect(db_nombre)
        self.cursor = self.conexion.cursor()
        self.cursor.execute('''CREATE TABLE IF NOT EXISTS usuarios (
                                id INTEGER PRIMARY KEY,
                                usuario TEXT NOT NULL,
                                contrasena TEXT NOT NULL
                                )''')
        self.conexion.commit()

    def agregar_usuario(self, usuario, contrasena):
        consulta = 'INSERT INTO usuarios (usuario, contrasena) VALUES (?, ?)'
        self.cursor.execute(consulta, (usuario, contrasena))
        self.conexion.commit()

    def verificar_credenciales(self, usuario, contrasena):
        consulta = 'SELECT * FROM usuarios WHERE usuario=? AND contrasena=?'
        self.cursor.execute(consulta, (usuario, contrasena))
        return self.cursor.fetchone() is not None

class LoginVista:
    def __init__(self, master, modelo, ventana_principal):
        self.master = master
        self.modelo = modelo
        self.ventana_principal = ventana_principal
        master.title('Inicio de Sesión')

        ttk.Label(master, text="Usuario:", font=("Arial",14)).place(x=500, y=200)
        ttk.Label(master, text="Contraseña:", font=("Arial",14)).place(x=490, y=300)

        self.usuario_entry = ttk.Entry(master)
        self.usuario_entry.place(x=600, y=200, width=150, height=20)
        self.contrasena_entry = ttk.Entry(master, show="*")
        self.contrasena_entry.place(x=600, y=300, width=150, height=20)

        self.iniciar_sesion_button = ttk.Button(master, text="Iniciar Sesión", command=self.iniciar_sesion)
        self.iniciar_sesion_button.place(x=600, y=400, width=150, height=50)
        self.registrar_button = ttk.Button(master, text="Registrarse", command=self.registrar)
        self.registrar_button.place(x=600, y=490, width=150, height=50)

    def iniciar_sesion(self):
        usuario = self.usuario_entry.get()
        contrasena = self.contrasena_entry.get()
        if self.modelo.verificar_credenciales(usuario, contrasena):
            messagebox.showinfo("Inicio de Sesión", "Inicio de sesión exitoso")
            self.ventana_principal.deiconify()  
            self.master.destroy()  
        else:
            messagebox.showerror("Inicio de Sesión", "Credenciales incorrectas")

    def registrar(self):
        usuario = self.usuario_entry.get()
        contrasena = self.contrasena_entry.get()
        if usuario and contrasena:
            self.modelo.agregar_usuario(usuario, contrasena)
            messagebox.showinfo("Registro exitoso", "Usuario registrado correctamente.")
        else:
            messagebox.showerror("Error", "Por favor, ingrese usuario y contraseña.")


class NegocioModelo:
    def __init__(self, db_nombre):
        self.conexion = sqlite3.connect(db_nombre)
        self.cursor = self.conexion.cursor()
        self.cursor.execute('''CREATE TABLE IF NOT EXISTS negocios (
                            linea TEXT PRIMARY KEY,
                            descripcion_corta TEXT,
                            descripcion_larga TEXT,
                            mascara TEXT)''')
        self.conexion.commit()
    
    def insertar(self, linea, descripcion_corta, descripcion_larga, mascara):
        consulta = 'INSERT INTO negocios VALUES (?, ?, ?, ?)'
        self.cursor.execute(consulta, (linea, descripcion_corta, descripcion_larga, mascara))
        self.conexion.commit()
    
    def consultar(self, linea):
        consulta = 'SELECT * FROM negocios WHERE linea=?'
        self.cursor.execute(consulta, (linea,))
        return self.cursor.fetchone()
    
    def eliminar(self, linea):
        consulta = 'DELETE FROM negocios WHERE linea=?'
        self.cursor.execute(consulta, (linea,))
        self.conexion.commit()
    
    def actualizar(self, linea, descripcion_corta, descripcion_larga, mascara):
        consulta = 'UPDATE negocios SET descripcion_corta=?, descripcion_larga=?, mascara=? WHERE linea=?'
        self.cursor.execute(consulta, (descripcion_corta, descripcion_larga, mascara, linea))
        self.conexion.commit()
    def consultar_todos(self):
        consulta = 'SELECT * FROM negocios'
        self.cursor.execute(consulta)
        return self.cursor.fetchall()


class NegocioVista:
    def __init__(self, master, controlador):
        self.master = master
        self.controlador = controlador
        master.title('Catálogo de Líneas de Negocio')
        tamaño_font=20
        
        # Campos de entrada
        self.linea_entry = tk.Entry(master, font=("Arial", tamaño_font))
        self.linea_entry.grid(row=0, column=1)
        self.descripcion_corta_entry = tk.Entry(master, font=("Arial", tamaño_font))
        self.descripcion_corta_entry.grid(row=2, column=1)
        self.descripcion_larga_text = tk.Text(master, height=10, width=30, font=("Arial", tamaño_font))  
        self.descripcion_larga_text.grid(row=4, column=1)
        self.mascara_entry = tk.Entry(master, font=("Arial", tamaño_font))
        self.mascara_entry.grid(row=8, column=1)

        # Etiquetas
        tk.Label(master, text="Línea de Negocio", font=("Arial", 20)).grid(row=0)
        tk.Label(master, text="Descripción Corta", font=("Arial", 20)).grid(row=2)
        tk.Label(master, text="Descripción Larga", font=("Arial", 20)).grid(row=4)
        tk.Label(master, text="Máscara", font=("Arial", 20)).grid(row=6)

        # Botones
        self.consulta_button = tk.Button(master, text="Consulta", command=self.consultar, font=("Arial", tamaño_font))
        self.consulta_button["bg"]="blue"
        self.consulta_button.place(x=700,y=195,width=200,height=50)
        self.alta_button = tk.Button(master, text="Alta", command=self.alta, font=("Arial", tamaño_font))
        self.alta_button["bg"]="green"
        self.alta_button.place(x=100,y=600,width=200,height=50)
        self.baja_button = tk.Button(master, text="Baja", command=self.baja, font=("Arial", tamaño_font))
        self.baja_button["bg"]="red"
        self.baja_button.place(x=400,y=600,width=200,height=50)
        self.cambio_button = tk.Button(master, text="Cambio", command=self.cambio, font=("Arial", tamaño_font))
        self.cambio_button["bg"]="blue"
        self.cambio_button.place(x=700,y=600,width=200,height=50)
        self.atras_button=tk.Button(master,text="<-", command=self.anterior, font=("Arial", tamaño_font))
        self.atras_button["bg"]="gray"
        self.atras_button.place(x=700,y=50,width=100,height=50)
        self.adelante_button=tk.Button(master,text="->", command=self.siguiente, font=("Arial", tamaño_font))
        self.adelante_button["bg"]="gray"
        self.adelante_button.place(x=800,y=50,width=100,height=50)
        self.resultados = []  
        self.index_actual = 0  

    def consultar(self):
        linea = self.linea_entry.get()
        negocio = self.controlador.consultar(linea)
        if negocio:
            self.descripcion_corta_entry.delete(0, tk.END)
            self.descripcion_corta_entry.insert(0, negocio[1])
            self.descripcion_larga_text.delete('1.0', tk.END)
            self.descripcion_larga_text.insert('1.0', negocio[2])
            self.mascara_entry.delete(0, tk.END)
            self.mascara_entry.insert(0, negocio[3])
            self.mostrar_resultado(self.resultados[0])
            self.index_actual = 0
        else:
            messagebox.showerror("Error", "Línea no encontrada.")
    def mostrar_resultado(self, negocio):
        self.descripcion_corta_entry.delete(0, tk.END)
        self.descripcion_corta_entry.insert(0, negocio[1])
        self.descripcion_larga_text.delete('1.0', tk.END)
        self.descripcion_larga_text.insert('1.0', negocio[2])
        self.mascara_entry.delete(0, tk.END)
        self.mascara_entry.insert(0, negocio[3])

    def anterior(self):
        if self.resultados:
            self.index_actual -= 1
            if self.index_actual < 0:
                self.index_actual = len(self.resultados) - 1
            self.mostrar_resultado(self.resultados[self.index_actual])
            
    def siguiente(self):
        if self.resultados:
            self.index_actual += 1
            if self.index_actual >= len(self.resultados):
                self.index_actual = 0
            self.mostrar_resultado(self.resultados[self.index_actual])

    def alta(self):
        linea = self.linea_entry.get()
        descripcion_corta = self.descripcion_corta_entry.get()
        descripcion_larga = self.descripcion_larga_text.get("1.0","end")
        mascara = self.mascara_entry.get()
        if not linea or not descripcion_corta or not descripcion_larga or not mascara:
            messagebox.showerror("Error", "Todos los campos son requeridos.")
        else:
            negocio = self.controlador.consultar(linea)
            if not negocio:
                self.controlador.insertar(linea, descripcion_corta, descripcion_larga, mascara)
                messagebox.showinfo("Éxito", "Registro insertado correctamente.")
            else:
                messagebox.showerror("Error", "La línea ya existe en el catálogo.")

    def baja(self):
        linea = self.linea_entry.get()
        negocio = self.controlador.consultar(linea)
        if negocio:
            self.controlador.eliminar(linea)
            messagebox.showinfo("Éxito", "Registro eliminado correctamente.")
        else:
            messagebox.showerror("Error", "Línea no encontrada.")

    def cambio(self):
        linea = self.linea_entry.get()
        descripcion_corta = self.descripcion_corta_entry.get()
        descripcion_larga = self.descripcion_larga_text.get("1.0","end")
        mascara = self.mascara_entry.get()
        negocio = self.controlador.consultar(linea)
        if negocio:
            self.controlador.actualizar(linea, descripcion_corta, descripcion_larga, mascara)
            messagebox.showinfo("Éxito", "Registro actualizado correctamente.")
        else:
            messagebox.showerror("Error", "Línea no encontrada.")


class NegocioControlador:
    def __init__(self, modelo):
        self.modelo = modelo
        
    def consultar(self, linea):
        return self.modelo.consultar(linea)
    
    def insertar(self, linea, descripcion_corta, descripcion_larga, mascara):
        self.modelo.insertar(linea, descripcion_corta, descripcion_larga, mascara)
    
    def eliminar(self, linea):
        self.modelo.eliminar(linea)
    
    def actualizar(self, linea, descripcion_corta, descripcion_larga, mascara):
        self.modelo.actualizar(linea, descripcion_corta, descripcion_larga, mascara)
    def consultar_todos(self):
        return self.modelo.consultar_todos()

def main():
    root = tk.Tk()
    root.geometry("1000x1000")
    modelo = NegocioModelo('negocios.db')
    controlador = NegocioControlador(modelo)
    vista = NegocioVista(root, controlador)
    modelo_usuario = UsuarioModelo('usuarios.db')
    ventana_login = tk.Toplevel(root)
    ventana_login.geometry("5000x5000")
    login_vista = LoginVista(ventana_login, modelo_usuario, root)

    root.withdraw()


    root.mainloop()
    



if __name__ == '__main__':
    main()

