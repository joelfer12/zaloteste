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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Aula03_1
{
    /// <summary>
    /// Interação lógica para MainWindow.xam
    /// </summary>
    public partial class MainWindow : Window
    {
        public List <Figura> Lista {  get; private set; }
        public MainWindow()
        {
            InitializeComponent();

            Lista = new List <Figura>();
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {

        }

        private void FiguraAdicionar_Click(object sender, RoutedEventArgs e)
        {
            WindowAdicionar p = new WindowAdicionar();
            if (p.ShowDialog() == true)
            {
                lbFiguras.Items.Add(p.NovaFigura.Nome);
                Lista.Add(p.NovaFigura);

            }
        }

        private void lbFiguras_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            int indice = lbFiguras.SelectedIndex;

            Figura selecionada = Lista[indice];

            sbDimensoes.Content = "Largura: " + selecionada.Largura + " Altura: " + selecionada.Altura;
        }
    }
}
