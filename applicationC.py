from flask import Flask, render_template, request, redirect, url_for, session, flash
from flask_mysqldb import MySQL, MySQLdb
from datetime import datetime
from decimal import Decimal

app = Flask(__name__, template_folder="C:\\Users\\mauro\\Desktop\\app04\\admin\\proyecto-final-bases-de-datos")
mysql = MySQL(app)

# Configuración para la conexión a la base de datos
app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = '/cyK2kHW#hWTVw&'
app.config['MYSQL_DB'] = 'sqlproyectofinalalex'
app.config['MYSQL_DATABASE_CHARSET'] = 'utf8mb4'
app.config['MYSQL_DATABASE_COLLATION'] = 'utf8mb4_general_ci'


# Clave secreta para la sesión de usuario
app.secret_key = b'_5#y2L"F4Q8z\n\xec]/'

@app.route('/')
def index():
    cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)

    # Obtener productos recomendados (los 3 más comprados)

    '''
    cur.execute("""
        SELECT p.id_producto, p.nombre_producto, p.precio, i.url_imagen, d.porcentaje
        FROM productos p
        LEFT JOIN (
            SELECT id_producto, url_imagen
            FROM imagenes
            GROUP BY id_producto
        ) i ON p.id_producto = i.id_producto
        LEFT JOIN descuentoss d ON p.id_producto = d.id_producto
        JOIN (
            SELECT id_producto, SUM(cantidad) as total_cantidad
            FROM detalle_pedidos
            GROUP BY id_producto
            ORDER BY total_cantidad DESC
            LIMIT 3
        ) dp ON p.id_producto = dp.id_producto
    """)
    '''
    cur.callproc('ObtenerProductosPopulares')
    productos_recomendados = cur.fetchall()
    cur.close()
    # Obtener productos con ofertas (los primeros 3)
    '''
    cur.execute("""
        SELECT p.id_producto, p.nombre_producto, p.precio, i.url_imagen, d.porcentaje
        FROM productos p
        LEFT JOIN (
            SELECT id_producto, url_imagen
            FROM imagenes
            GROUP BY id_producto
        ) i ON p.id_producto = i.id_producto
        LEFT JOIN descuentoss d ON p.id_producto = d.id_producto
        WHERE d.porcentaje IS NOT NULL
        LIMIT 3
    """)
    '''
    cur = mysql.connection.cursor()
    cur.callproc('ObtenerProductosConDescuento')
    productos_oferta = cur.fetchall()
    cur.close()
    # Obtener categorías
    #cur.execute("SELECT id_categoria, nombre_categoria, imagen_url FROM categorias")
    cur = mysql.connection.cursor()
    cur.callproc('ObtenerCategorias')
    categorias = cur.fetchall()
    cur.close()
    # Obtener marcas
    #cur.execute("SELECT id_marca, nombre_marca, imagen_url FROM marcas")
    cur = mysql.connection.cursor()
    cur.callproc('ObtenerMarcas')
    marcas = cur.fetchall()
    cur.close()

    for producto in productos_recomendados:
        if producto['porcentaje']:
            porcentaje_decimal = Decimal(producto['porcentaje']) / Decimal(100)
            producto['precio_final'] = producto['precio'] * (1 - porcentaje_decimal)
        else:
            producto['precio_final'] = producto['precio']
    # Convertir la lista de tuplas a una lista de diccionarios
    productos_oferta_con_diccionario = []
    for producto in productos_oferta:
        producto_dict = {
            'id_producto': producto[0],
            'nombre_producto': producto[1],
            'precio': producto[2],
            'url_imagen': producto[3],
            'porcentaje': producto[4],
        }
        productos_oferta_con_diccionario.append(producto_dict)

    # Calcular el precio final y agregarlo al diccionario
    for producto in productos_oferta_con_diccionario:
        if producto['porcentaje']:
            porcentaje_decimal = Decimal(producto['porcentaje']) / Decimal(100)
            producto['precio_final'] = producto['precio'] * (1 - porcentaje_decimal)
        else:
            producto['precio_final'] = producto['precio']




    if 'user_id' in session:
        user_id = session['user_id']
        cur = mysql.connection.cursor()
        #cur.execute("SELECT nombre, apellido FROM clientes WHERE id_cliente = %s", (user_id,))
        cur.callproc('ObtenerNombreApellidoCliente',(user_id,))
        user_data = cur.fetchone()
        cur.close()
        if user_data:
            nombre, apellido = user_data
            return render_template('index.html', logged_in=True, nombre=nombre, apellido=apellido, productos_recomendados=productos_recomendados, productos_oferta=productos_oferta_con_diccionario, categorias=categorias, marcas=marcas)
    return render_template('index.html', logged_in=False, productos_recomendados=productos_recomendados, productos_oferta=productos_oferta_con_diccionario, categorias=categorias, marcas=marcas)


@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        cur = mysql.connection.cursor()
        #cur.execute("SELECT id_cliente, usuario, contrasena FROM logins WHERE usuario = %s", (username,))
        cur.callproc('ObtenerLoginPorUsuario',(username,))
        user = cur.fetchone()
        cur.close()

        if user and password == user[2]:
            session['user_id'] = user[0]
            session['username'] = username
            return redirect(url_for('index'))
        else:
            return "Usuario o contraseña incorrectos"

    return render_template('login.html')

@app.route('/logout')
def logout():
    session.pop('user_id', None)
    session.pop('username', None)
    return redirect(url_for('index'))

@app.route('/registro', methods=['GET', 'POST'])
def registro():
    if request.method == 'POST':
        nombre = request.form['nombre']
        apellido = request.form['apellido']
        email = request.form['email']
        usuario = request.form['usuario']
        contrasena = request.form['contrasena']
        fecha_ingreso = datetime.now().strftime('%Y-%m-%d')
        
        cur = mysql.connection.cursor()
        #cur.execute('SELECT * FROM clientes WHERE email = %s', (email,))
        cur.callproc('ObtenerClientePorEmail',(email,))
        email_exists = cur.fetchone()
        cur.close()
        #cur.execute('SELECT * FROM logins WHERE usuario = %s', (usuario,))
        cur = mysql.connection.cursor()
        cur.callproc('ObtenerLoginPorUsuario',(usuario,))
        user_exists = cur.fetchone()
        cur.close()
        
        if email_exists:
            flash('El correo electrónico ya está registrado')
        elif user_exists:
            flash('El nombre de usuario ya está registrado')
        else:
            #cur.execute('INSERT INTO clientes (nombre, apellido, fecha_ingreso, email) VALUES (%s, %s, %s, %s)', (nombre, apellido, fecha_ingreso, email))
            cur = mysql.connection.cursor()
            cur.callproc('InsertarCliente',(nombre, apellido, fecha_ingreso, email))
            mysql.connection.commit()
            id_cliente = cur.lastrowid
            cur.close()
            #cur.execute('INSERT INTO logins (id_cliente, usuario, contrasena) VALUES (%s, %s, %s)', (id_cliente, usuario, contrasena))
            cur = mysql.connection.cursor()
            cur.callproc('InsertarLogin',(id_cliente,usuario,contrasena))
            cur.close()
            mysql.connection.commit()
            flash('Registro exitoso, por favor inicia sesión')
            return redirect(url_for('login'))
        
    return render_template('registro.html')

@app.route('/account')
def account():
    if 'user_id' in session:
        return render_template('cuenta.html')
    return redirect(url_for('login'))

@app.route('/addresses', methods=['GET', 'POST'])
def addresses():
    if 'user_id' in session:
        user_id = session['user_id']
        if request.method == 'POST':
            # Procesar la adición, edición o eliminación de direcciones
            action = request.form.get('action')
            if action == 'add':
                calle = request.form['calle']
                colonia = request.form['colonia']
                codigo_postal = request.form['codigo_postal']
                ciudad = request.form['ciudad']
                estado = request.form['estado']
                pais = request.form['pais']
                if all([calle, colonia, codigo_postal, ciudad, estado, pais]):
                    cur = mysql.connection.cursor()
                    #cur.execute("INSERT INTO direccion_clientes (id_cliente, calle, colonia, codigo_postal, ciudad, estado, pais) VALUES (%s, %s, %s, %s, %s, %s, %s)", 
                    #            (user_id, calle, colonia, codigo_postal, ciudad, estado, pais))
                    cur.callproc('InsertarDireccionCliente',(user_id, calle, colonia, codigo_postal, ciudad, estado, pais))
                    mysql.connection.commit()
                    cur.close()
                    flash("Dirección agregada correctamente")
                else:
                    flash("Todos los campos son obligatorios")

            elif action == 'edit':
                id_direccion = request.form['id_direccion']
                calle = request.form['calle']
                colonia = request.form['colonia']
                codigo_postal = request.form['codigo_postal']
                ciudad = request.form['ciudad']
                estado = request.form['estado']
                pais = request.form['pais']
                if all([calle, colonia, codigo_postal, ciudad, estado, pais]):
                    cur = mysql.connection.cursor()
                    #cur.execute("UPDATE direccion_clientes SET calle=%s, colonia=%s, codigo_postal=%s, ciudad=%s, estado=%s, pais=%s WHERE id_direccion_cliente=%s AND id_cliente=%s", 
                    #            (calle, colonia, codigo_postal, ciudad, estado, pais, id_direccion, user_id))
                    cur.callproc('ActualizarDireccionCliente',(calle, colonia, codigo_postal, ciudad, estado, pais, id_direccion, user_id))
                    mysql.connection.commit()
                    cur.close()
                    flash("Dirección actualizada correctamente")
                else:
                    flash("Todos los campos son obligatorios")

            elif action == 'delete':
                id_direccion = request.form['id_direccion']
                cur = mysql.connection.cursor()
                #cur.execute("DELETE FROM direccion_clientes WHERE id_direccion_cliente=%s AND id_cliente=%s", (id_direccion, user_id))
                cur.callproc('EliminarDireccionCliente',(id_direccion, user_id))
                mysql.connection.commit()
                cur.close()
                flash("Dirección eliminada correctamente")

        # Obtener todas las direcciones del usuario
        cur = mysql.connection.cursor()
        #cur.execute("SELECT id_direccion_cliente, calle, colonia, codigo_postal, ciudad, estado, pais FROM direccion_clientes WHERE id_cliente = %s", (user_id,))
        cur.callproc('ObtenerDireccionesCliente',(user_id,))
        addresses = cur.fetchall()
        cur.close()
        return render_template('direcciones.html', addresses=addresses)
    return redirect(url_for('login'))

@app.route('/history')
def history():
    if 'user_id' in session:
        user_id = session['user_id']
        cur = mysql.connection.cursor()
        '''
        cur.execute("""
            SELECT p.id_pedido, pr.nombre_producto, dp.cantidad, pr.precio, ep.nombre as estado
            FROM pedidos p
            JOIN detalle_pedidos dp ON p.id_pedido = dp.id_pedido
            JOIN productos pr ON dp.id_producto = pr.id_producto
            JOIN estado_pedidos ep ON p.id_estado_pedido = ep.id_estado_pedido
            WHERE p.id_cliente = %s
        """, (user_id,))
        '''
        cur.callproc('ObtenerDetallesPedidoPorCliente',(user_id,))
        orders = cur.fetchall()
        cur.close()
        return render_template('historial.html', orders=orders)
    return redirect(url_for('login'))

@app.route('/productos')
def productos():
    if 'user_id' not in session:
        flash("Por favor, inicia sesión para ver los productos.")
        return redirect(url_for('login'))

    user_id = session['user_id']
    cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)  # Configurar el cursor para devolver un diccionario
    cur.callproc('ObtenerNombreApellidoCliente',(user_id,))
    user_data = cur.fetchone()
    cur.close()

    cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)  # Configurar el cursor para devolver un diccionario
    cur.callproc('ObtenerProductos')
    productos = cur.fetchall()
    cur.close()

    for producto in productos:
        if producto['porcentaje']:
            porcentaje_decimal = Decimal(producto['porcentaje']) / Decimal(100)
            producto['precio_final'] = producto['precio'] * (1 - porcentaje_decimal)
        else:
            producto['precio_final'] = producto['precio']
    if user_data:
        nombre = user_data['nombre']
        apellido = user_data['apellido']
        return render_template('productos.html', logged_in=True, nombre=nombre, apellido=apellido, productos=productos)
    else:
        return render_template('productos.html', logged_in=False, productos=productos)  # Manejar el caso en el que no hay usuario

@app.route('/detalles/<int:id_producto>', methods=['GET', 'POST'])
def detalles(id_producto):
    if 'user_id' not in session:
        flash("Por favor, inicia sesión para ver los detalles del producto.")
        return redirect(url_for('login'))

    if request.method == 'POST':
        user_id = session['user_id']
        calificacion = request.form['calificacion']
        resena = request.form['resena']
        fecha = datetime.now().strftime('%Y-%m-%d')

        cur = mysql.connection.cursor()
        #cur.execute("INSERT INTO resenas (id_cliente, id_producto, reseña, calificacion, fecha) VALUES (%s, %s, %s, %s, %s)", (user_id, id_producto, resena, calificacion, fecha))
        cur.callproc('InsertarResena',(user_id, id_producto, resena, calificacion, fecha))
        mysql.connection.commit()
        cur.close()

    user_id = session['user_id']
    cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
    #cur.execute("SELECT nombre, apellido FROM clientes WHERE id_cliente = %s", (user_id,))
    cur.callproc('ObtenerNombreApellidoCliente',(user_id,))
    user_data = cur.fetchone()
    cur.close()
    '''
    cur.execute("""
        SELECT p.id_producto, p.nombre_producto, p.descripcion_producto, p.precio, i.url_imagen, d.porcentaje
        FROM productos p
        LEFT JOIN imagenes i ON p.id_producto = i.id_producto
        LEFT JOIN descuentoss d ON p.id_producto = d.id_producto
        WHERE p.id_producto = %s
    """, (id_producto,))
    '''
    cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
    cur.callproc('ObtenerDetallesProducto',(id_producto,))
    producto = cur.fetchone()
    cur.close()

    #cur.execute("SELECT url_imagen FROM imagenes WHERE id_producto = %s", (id_producto,))
    cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
    cur.callproc('ObtenerURLImagenProducto',(id_producto,))
    imagenes = cur.fetchall()
    cur.close()
    '''
    cur.execute("""
        SELECT r.reseña, r.calificacion, r.fecha, c.nombre, c.apellido
        FROM resenas r
        JOIN clientes c ON r.id_cliente = c.id_cliente
        WHERE r.id_producto = %s
    """, (id_producto,))
    '''
    cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
    cur.callproc('ObtenerResenasProducto',(id_producto,))
    resenas = cur.fetchall()
    cur.close()
    '''
    cur.execute("""
        SELECT COUNT(*) as total_resenas, AVG(calificacion) as promedio_calificacion
        FROM resenas
        WHERE id_producto = %s
    """, (id_producto,))
    '''
    cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
    cur.callproc('ObtenerEstadisticasResenas',(id_producto,))
    resena_info = cur.fetchone()
    cur.close()

    if user_data:
        nombre = user_data['nombre']
        apellido = user_data['apellido']
        return render_template('detalles.html', logged_in=True, nombre=nombre, apellido=apellido, producto=producto, imagenes=imagenes, resenas=resenas, resena_info=resena_info)
    return render_template('detalles.html', logged_in=False, producto=producto, imagenes=imagenes, resenas=resenas, resena_info=resena_info)

@app.route('/agregar_carrito/<int:id_producto>')
def agregar_carrito(id_producto):
    if 'user_id' not in session:
        flash("Por favor, inicia sesión para agregar productos al carrito.")
        return redirect(url_for('login'))
    
    user_id = session['user_id']
    cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
    
    # Obtener o crear carrito del usuario
    #cur.execute("SELECT id_carrito FROM carritos WHERE id_cliente = %s", (user_id,))
    cur.callproc('ObtenerIDCarritoPorCliente',(user_id,))
    carrito = cur.fetchone()
    if not carrito:
        # No se encontró ningún carrito asociado al usuario, crear uno nuevo
        cur.callproc('InsertarCarrito',(user_id,))
        mysql.connection.commit()
        carrito_id = cur.lastrowid
    else:
        carrito_id = carrito.get('id_carrito')

    cur.close()
    # Verificar si el producto ya está en el carrito
    #cur.execute("SELECT cantidad FROM detalle_carritos WHERE id_carrito = %s AND id_producto = %s", (carrito_id, id_producto))
    cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
    cur.callproc('ObtenerCantidadProductoEnCarrito',(carrito_id,id_producto))
    detalle = cur.fetchone()
    

    cur.close()
    
    flash("Producto agregado al carrito.")
    return redirect(url_for('carrito'))



@app.route('/carrito', methods=['GET', 'POST'])
def carrito():
    if 'user_id' not in session:
        flash("Por favor, inicia sesión para ver tu carrito.")
        return redirect(url_for('login'))
    
    user_id = session['user_id']
    cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
    
    # Obtener productos en el carrito
    '''
    cur.execute("""
    SELECT p.id_producto, p.nombre_producto, p.precio, dc.cantidad, i.url_imagen, d.porcentaje, s.cantidad_stock
    FROM detalle_carritos dc
    JOIN carritos c ON dc.id_carrito = c.id_carrito
    JOIN productos p ON dc.id_producto = p.id_producto
    LEFT JOIN descuentoss d ON p.id_producto = d.id_producto
    LEFT JOIN (
        SELECT id_producto, url_imagen
        FROM imagenes
        GROUP BY id_producto
    ) i ON p.id_producto = i.id_producto
    JOIN stocks s ON p.id_stock = s.id_stock
    WHERE c.id_cliente = %s
    """, (user_id,))
    '''
    cur.callproc('ObtenerDetallesProductosCarrito',(user_id,))
    items = cur.fetchall()
    
    total = sum((item['precio'] * (1 - item['porcentaje'] / 100) if item['porcentaje'] else item['precio']) * item['cantidad'] for item in items)
    
    if request.method == 'POST':
        action = request.form.get('action')
        if action == 'update':
            id_producto = request.form.get('id_producto')
            nueva_cantidad = int(request.form.get('cantidad'))
            #cur.execute("UPDATE detalle_carritos SET cantidad = %s WHERE id_producto = %s AND id_carrito IN (SELECT id_carrito FROM carritos WHERE id_cliente = %s)", (nueva_cantidad, id_producto, user_id))
            cur.callproc('ActualizarCantidadProductoEnCarritosCliente',(nueva_cantidad, id_producto, user_id))
            mysql.connection.commit()
            flash("Cantidad actualizada.")
        elif action == 'delete':
            id_producto = request.form.get('id_producto')
            #cur.execute("DELETE FROM detalle_carritos WHERE id_producto = %s AND id_carrito IN (SELECT id_carrito FROM carritos WHERE id_cliente = %s)", (id_producto, user_id))
            cur.callproc('EliminarDetalleProductoEnCarritosCliente',(id_producto, user_id))
            mysql.connection.commit()
            flash("Producto eliminado del carrito.")
        elif action == 'add_address':
            calle = request.form['calle']
            colonia = request.form['colonia']
            codigo_postal = request.form['codigo_postal']
            ciudad = request.form['ciudad']
            estado = request.form['estado']
            pais = request.form['pais']
            if all([calle, colonia, codigo_postal, ciudad, estado, pais]):
                #cur.execute("INSERT INTO direccion_clientes (id_cliente, calle, colonia, codigo_postal, ciudad, estado, pais) VALUES (%s, %s, %s, %s, %s, %s, %s)", 
                #            (user_id, calle, colonia, codigo_postal, ciudad, estado, pais))
                cur.callproc('InsertarDireccionCliente',(user_id, calle, colonia, codigo_postal, ciudad, estado, pais))
                mysql.connection.commit()
                flash("Dirección agregada correctamente.")
            else:
                flash("Todos los campos son obligatorios para agregar una nueva dirección.")
        elif action == 'comprar':
            direccion_id = request.form.get('direccion')
            metodo_pago_id = request.form.get('metodo_pago')
            # Lógica de compra aquí (No implementada en este ejemplo)
            flash("Compra realizada con éxito.")
        
        return redirect(url_for('carrito'))
    cur.close()
    cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
    # Obtener direcciones del usuario
    #cur.execute("SELECT id_direccion_cliente, calle, colonia, codigo_postal, ciudad, estado, pais FROM direccion_clientes WHERE id_cliente = %s", (user_id,))
    cur.callproc('ObtenerDireccionesCliente',(user_id,))
    direcciones = cur.fetchall()
    cur.close()
    # Obtener métodos de pago
    #cur.execute("SELECT id_metodo_pago, metodo_pago FROM metodo_pagos")
    cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
    cur.callproc('ObtenerMetodosPago')
    metodos_pago = cur.fetchall()
    
    cur.close()

    return render_template('carrito.html', items=items, total=total, direcciones=direcciones, metodos_pago=metodos_pago)

@app.route('/categoria/<int:id_categoria>')
def categoria(id_categoria):
    cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
    
    if 'user_id' in session:
        user_id = session['user_id']
        #cur.execute("SELECT nombre, apellido FROM clientes WHERE id_cliente = %s", (user_id,))
        cur.callproc('ObtenerNombreApellidoCliente',(user_id,))
        user_data = cur.fetchone()
        cur.close()
        #cur.execute("SELECT nombre_categoria FROM categorias WHERE id_categoria = %s", (id_categoria,))
        cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
        cur.callproc('ObtenerNombreCategoria',(id_categoria,))
        categoria = cur.fetchone()
        cur.close()
        '''
        cur.execute("""
            SELECT p.id_producto, p.nombre_producto, p.precio, i.url_imagen, d.porcentaje
            FROM productos p
            LEFT JOIN (
                SELECT id_producto, url_imagen
                FROM imagenes
                GROUP BY id_producto
            ) i ON p.id_producto = i.id_producto
            LEFT JOIN descuentoss d ON p.id_producto = d.id_producto
            WHERE p.id_categoria = %s
        """, (id_categoria,))
        '''
        cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
        cur.callproc('ObtenerProductosPorCategoria',(id_categoria,))
        productos = cur.fetchall()
        cur.close()
        for producto in productos:
            if producto['porcentaje']:
                porcentaje_decimal = Decimal(producto['porcentaje']) / Decimal(100)
                producto['precio_final'] = producto['precio'] * (1 - porcentaje_decimal)
            else:
                producto['precio_final'] = producto['precio']
        
        if user_data:
            nombre = user_data['nombre']
            apellido = user_data['apellido']
            return render_template('categoria.html', logged_in=True, nombre=nombre, apellido=apellido, categoria=categoria, productos=productos)
    else:
        #cur.execute("SELECT nombre_categoria FROM categorias WHERE id_categoria = %s", (id_categoria,))
        cur.callproc('ObtenerNombreCategoria',(id_categoria,))
        categoria = cur.fetchone()
        '''
        cur.execute("""
            SELECT p.id_producto, p.nombre_producto, p.precio, i.url_imagen, d.porcentaje
            FROM productos p
            LEFT JOIN (
                SELECT id_producto, url_imagen
                FROM imagenes
                GROUP BY id_producto
            ) i ON p.id_producto = i.id_producto
            LEFT JOIN descuentoss d ON p.id_producto = d.id_producto
            WHERE p.id_categoria = %s
        """, (id_categoria,))
        '''
        cur.callproc('ObtenerProductosPorCategoria',(id_categoria,))
        productos = cur.fetchall()
        cur.close()
        
    return render_template('categoria.html', logged_in=False, categoria=categoria, productos=productos)

@app.route('/marca/<int:id_marca>')
def marca(id_marca):
    if 'user_id' not in session:
        flash("Por favor, inicia sesión para ver los productos de esta marca.")
        return redirect(url_for('login'))

    user_id = session['user_id']
    cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
    #cur.execute("SELECT nombre, apellido FROM clientes WHERE id_cliente = %s", (user_id,))
    cur.callproc('ObtenerNombreApellidoCliente',(user_id,))
    user_data = cur.fetchone()
    cur.close()
    #cur.execute("SELECT nombre_marca FROM marcas WHERE id_marca = %s", (id_marca,))
    cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
    cur.callproc('ObtenerNombreMarca',(id_marca,))
    marca = cur.fetchone()
    cur.close()
    '''
    cur.execute("""
        SELECT p.id_producto, p.nombre_producto, p.precio, i.url_imagen, d.porcentaje
        FROM productos p
        LEFT JOIN (
            SELECT id_producto, url_imagen
            FROM imagenes
            GROUP BY id_producto
        ) i ON p.id_producto = i.id_producto
        LEFT JOIN descuentoss d ON p.id_producto = d.id_producto
        WHERE p.id_marca = %s
    """, (id_marca,))
    '''
    cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
    cur.callproc('ObtenerProductosPorMarca',(id_marca,))
    productos = cur.fetchall()
    cur.close()
    for producto in productos:
            if producto['porcentaje']:
                porcentaje_decimal = Decimal(producto['porcentaje']) / Decimal(100)
                producto['precio_final'] = producto['precio'] * (1 - porcentaje_decimal)
            else:
                producto['precio_final'] = producto['precio']
    if user_data:
        nombre = user_data['nombre']
        apellido = user_data['apellido']
        return render_template('marca.html', logged_in=True, nombre=nombre, apellido=apellido, marca=marca, productos=productos)
    return render_template('marca.html', logged_in=False, marca=marca, productos=productos)


@app.route('/ofertas')
def ofertas():
    cur = mysql.connection.cursor(MySQLdb.cursors.DictCursor)
    '''
    cur.execute("""
        SELECT p.id_producto, p.nombre_producto, p.precio, i.url_imagen, d.porcentaje
        FROM productos p
        LEFT JOIN (
            SELECT id_producto, url_imagen
            FROM imagenes
            GROUP BY id_producto
        ) i ON p.id_producto = i.id_producto
        LEFT JOIN descuentoss d ON p.id_producto = d.id_producto
        WHERE d.porcentaje IS NOT NULL
    """)
    '''

    cur.callproc('ObtenerProductosConDescuento')
    productos_oferta = cur.fetchall()
    cur.close()
    for producto in productos_oferta:
            if producto['porcentaje']:
                porcentaje_decimal = Decimal(producto['porcentaje']) / Decimal(100)
                producto['precio_final'] = producto['precio'] * (1 - porcentaje_decimal)
            else:
                producto['precio_final'] = producto['precio']
    return render_template('ofertas.html', productos_oferta=productos_oferta)

@app.route('/comprar', methods=['POST'])
def comprar():
    if 'user_id' not in session:
        flash("Por favor, inicia sesión para realizar una compra.")
        return redirect(url_for('login'))

    user_id = session['user_id']
    direccion_id = request.form.get('direccion')
    metodo_pago = request.form.get('metodo_pago')

    cur = mysql.connection.cursor()

    # Crear nuevo pedido
    #cur.execute("INSERT INTO pedidos (id_cliente, id_estado_pedido) VALUES (%s, 1)", (user_id,))
    cur.callproc('InsertarPedido',(user_id,))
    mysql.connection.commit()
    id_pedido = cur.lastrowid

    # Obtener items del carrito
    '''
    cur.execute("""
        SELECT dc.id_producto, p.precio, IFNULL(d.porcentaje, 0), dc.cantidad
        FROM detalle_carritos dc
        JOIN productos p ON dc.id_producto = p.id_producto
        LEFT JOIN descuentoss d ON p.id_producto = d.id_producto
        WHERE dc.id_carrito = (SELECT id_carrito FROM carritos WHERE id_cliente = %s)
    """, (user_id,))
    '''
    cur.callproc('ObtenerDetallesProductoEnCarrito',(user_id,))
    items = cur.fetchall()

    # Insertar detalles del pedido
    for item in items:
        precio_final = item[1] * (1 - item[2] / 100) if item[2] else item[1]
        #cur.execute("INSERT INTO detalle_pedidos (id_pedido, id_producto, cantidad) VALUES (%s, %s, %s)", 
        #            (id_pedido, item[0], item[3]))
        cur.callproc('InsertarDetallePedido',(id_pedido,item[0],item[3]))

    # Insertar historial del pedido
    fecha_pedido = datetime.now().strftime('%Y-%m-%d')
    #cur.execute("INSERT INTO historial_pedidos (id_pedido, fecha_pedido) VALUES (%s, %s)", 
    #            (id_pedido, fecha_pedido))
    cur.callproc('InsertarHistorialPedido',(id_pedido,fecha_pedido))
    
    # Limpiar el carrito
    #cur.execute("DELETE FROM detalle_carritos WHERE id_carrito = (SELECT id_carrito FROM carritos WHERE id_cliente = %s)", 
    #            (user_id,))
    cur.callproc('EliminarDetalleCarritoPorCliente',(user_id,))
    mysql.connection.commit()
    cur.close()

    return render_template('compra.html', mensaje="Gracias por comprar en TIENDA.COM!")


# Route for the confirmation page
@app.route('/compra')
def compra():
    if 'user_id' not in session:
        return redirect(url_for('login'))
    return render_template('compra.html')


if __name__ == '__main__':
    app.run(debug=True)
