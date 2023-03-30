using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Aula03_1
{
    /// <summary>
    /// Lógica interna para WindowAdicionar.xaml
    /// </summary>
    public partial class WindowAdicionar : Window
    {
       public Figura NovaFigura { get; private set; }
        public WindowAdicionar()
        {
            InitializeComponent();

            NovaFigura = new Figura();
        }

        private void btnCancelar_Click(object sender, RoutedEventArgs e)
        {
            this.DialogResult = false;
        }

        private void btnAdicionar_Click(object sender, RoutedEventArgs e)
        {
            this.DialogResult = true;

            NovaFigura.Largura = tbLargura.Text;
            NovaFigura.Altura = tbAltura.Text;

            if (rbQuadrado.IsChecked == true)
                Convert.ToInt32(NovaFigura.Largura);
                if (NovaFigura.Largura) = Convert.ToInt32(NovaFigura.Largura))
                {
                    NovaFigura.Nome = "Quadrado";
                } //Experimentar
                
            else if (rbRetangulo.IsChecked == true)
                NovaFigura.Nome = "Retângulo";
            else
                NovaFigura.Nome = "Circulo";

            
        }
    }
}
