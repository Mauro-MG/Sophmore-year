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
    '''
    cur.execute("""
        SELECT p.id_producto, p.nombre_producto, p.descripcion_producto, p.precio, i.url_imagen, d.porcentaje
        FROM productos p
        LEFT JOIN imagenes i ON p.id_producto = i.id_producto
        LEFT JOIN descuentoss d ON p.id_producto = d.id_producto
        WHERE p.id_producto = %s
    """, (id_producto,))
    '''
    cur.callproc('ObtenerDetallesProducto',(id_producto,))
    producto = cur.fetchone()

    #cur.execute("SELECT url_imagen FROM imagenes WHERE id_producto = %s", (id_producto,))
    cur.callproc('ObtenerURLImagenProducto',(id_producto,))
    imagenes = cur.fetchall()
    '''
    cur.execute("""
        SELECT r.reseña, r.calificacion, r.fecha, c.nombre, c.apellido
        FROM resenas r
        JOIN clientes c ON r.id_cliente = c.id_cliente
        WHERE r.id_producto = %s
    """, (id_producto,))
    '''
    cur.callproc('ObtenerResenasProducto',(id_producto,))
    resenas = cur.fetchall()
    '''
    cur.execute("""
        SELECT COUNT(*) as total_resenas, AVG(calificacion) as promedio_calificacion
        FROM resenas
        WHERE id_producto = %s
    """, (id_producto,))
    '''
    cur.callproc('ObtenerEstadisticasResenas',(id_producto,))
    resena_info = cur.fetchone()

    cur.close()

    if user_data:
        nombre = user_data['nombre']
        apellido = user_data['apellido']
        return render_template('detalles.html', logged_in=True, nombre=nombre, apellido=apellido, producto=producto, imagenes=imagenes, resenas=resenas, resena_info=resena_info)
    return render_template('detalles.html', logged_in=False, producto=producto, imagenes=imagenes, resenas=resenas, resena_info=resena_info)
