#from fpdf import FPDF

# Crear un objeto de clase FPDF
#pdf = FPDF()

# Agregar una página
#pdf.add_page()

# Establecer la fuente y el tamaño de la letra para el título
#pdf.set_font('Arial', 'B', 16)

# Escribir el título
#pdf.cell(0, 10, 'Mi Currículum Vitae', 0, 1, 'C')

# Agregar una línea en blanco
#pdf.cell(0, 10, '', 0, 1)

# Establecer la fuente y el tamaño de la letra para la información personal
#pdf.set_font('Arial', '', 12)

# Escribir la información personal
#pdf.cell(0, 10, 'Nombre: Juan Pérez', 0, 1)
#pdf.cell(0, 10, 'Edad: 25 años', 0, 1)
#pdf.cell(0, 10, 'Correo electrónico: juan.perez@gmail.com', 0, 1)

# Guardar el documento PDF
#pdf.output('mi_cv.pdf', 'F')

from flask import Flask, Response
from fpdf import FPDF

app = Flask(__name__)

class PDF(FPDF):
   # def header(self):
        # Insertar imagen de encabezado
        #self.image('header.png', 0, 0, 210)

    def footer(self):
        # Número de página
        self.set_y(-10)
        self.set_font('Arial', 'I', 8)
        self.cell(0, 10, 'Página ' + str(self.page_no()), 0, 0, 'C')

@app.route("/")
def generate_pdf():
    pdf = PDF()
    pdf.add_page()

    # Título del currículum
    pdf.set_font('Arial', 'B', 16)
    pdf.cell(0, 20, 'Currículum Vitae', 0, 1, 'C')

    # Información personal
    pdf.set_font('Arial', 'B', 14)
    pdf.cell(0, 10, 'Información Personal', 0, 1)
    pdf.set_font('Arial', '', 12)
    pdf.cell(0, 10, 'Nombre: [Nombre completo]', 0, 1)
    pdf.cell(0, 10, 'Dirección: [Dirección completa]', 0, 1)
    pdf.cell(0, 10, 'Correo electrónico: [Correo electrónico]', 0, 1)
    pdf.cell(0, 10, 'Teléfono: [Número de teléfono]', 0, 1)

    # Experiencia laboral
    pdf.set_font('Arial', 'B', 14)
    pdf.cell(0, 10, 'Experiencia Laboral', 0, 1)
    pdf.set_font('Arial', '', 12)
    pdf.cell(0, 10, '[Nombre de la empresa]', 0, 1)
    pdf.cell(0, 10, '[Cargo]', 0, 1)
    pdf.cell(0, 10, '[Fecha de inicio] - [Fecha de finalización]', 0, 1)
    pdf.cell(0, 10, '[Descripción de las responsabilidades]', 0, 1)

    # Educación
    pdf.set_font('Arial', 'B', 14)
    pdf.cell(0, 10, 'Educación', 0, 1)
    pdf.set_font('Arial', '', 12)
    pdf.cell(0, 10, '42 Madrid', 0, 1)
    pdf.cell(0, 10, 'Ingeniería Informática', 0, 1)
    pdf.cell(0, 10, 'Fecha de inicio - Fecha de finalización', 0, 1)
    pdf.cell(0, 10, '[Descripción de los proyectos desarrollados]', 0, 1)

    # Habilidades y competencias
    pdf.set_font('Arial', 'B', 14)
    pdf.cell(0, 10, 'Habilidades y Competencias', 0, 1)
    pdf.set_font('Arial', '', 12)
    pdf.cell(0, 10, '- Lenguajes de programación: [Lista de lenguajes]', 0, 1)
    pdf.cell(0, 10, '- Herramientas de desarrollo: [Lista de herramientas]', 0, 1)
    return Response(pdf.output(dest='S').encode('latin-1'), mimetype='application/pdf')
def main():
    app.run(port=5000, debug=True)

if __name__ == "__main__":
    main()


