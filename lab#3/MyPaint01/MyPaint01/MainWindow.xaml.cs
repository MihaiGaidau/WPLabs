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
using System.Windows.Controls.Primitives;

namespace MyPaint01
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Document doc;   //Trang hiện tại của ứng dụng.
        private Point mDown, mMove;
        private bool capture;   //Trạng thái vẽ: dragging hoặc vẽ thật
        private ContentControl curControl;
        private Shape curShape;
        private Line curLine;
        private Color fillColor, penColor;
        private double penThickness;
        private PathGeometry pathGeometry;
        private Path path;
        private PathFigure pathFigure;
        private string currentFilePath;
        private ContentControl selectedControl;
        private TextBox focusedTextbox;
        /// <Text Adjustment>
        private FontFamily fontFamily;
        private double fontSize;
        private FontStyle fontStyle;
        private FontWeight fontWeight;
        private TextDecorationCollection decoration;
        private Color fontColor;
        bool bold = false, italic = false, underlined = false;
        float oldLineCount;
        /// </Text Adjustment>
       
        public MainWindow()
        {
            InitializeComponent();
            doc = new Document(paintCanvas);
            capture = false;
            penColor = Colors.Black;
            fillColor = Colors.Black;
            penThickness = 1;
            btnSmooth.IsChecked = true;
            

        }

        private void My_Paint_Loaded(object sender, RoutedEventArgs e)
        {
            fontFamily = new FontFamily(cbxFontFamily.Items[cbxFontFamily.SelectedIndex].ToString());
            fontSize = 8;
            fontColor = Colors.Black;
            fontStyle = FontStyles.Normal;
            fontWeight = FontWeights.Normal;
            decoration = null;
            txtWidth.Text = doc.canvas.Width.ToString();
            txtHeight.Text = doc.canvas.Height.ToString();
        }

        private void btnPointer_Click(object sender, RoutedEventArgs e)
        {
            doc.drawType = DrawType.nothing;
            paintCanvas.Cursor = Cursors.Arrow;
        }

        private void btnPencil_Click(object sender, RoutedEventArgs e)
        {
            doc.drawType = DrawType.pencil;
            paintCanvas.Cursor = Cursors.Pen;
        }

        private void btnBrush_Click(object sender, RoutedEventArgs e)
        {
            doc.drawType = DrawType.brush;
            penThickness = 3;
            paintCanvas.Cursor = Cursors.Pen;
        }

        private void btnLine_Click(object sender, RoutedEventArgs e)
        {
            doc.drawType = DrawType.line;
            paintCanvas.Cursor = Cursors.Cross;
        }

        private void btnEllipse_Click(object sender, RoutedEventArgs e)
        {
            doc.drawType = DrawType.ellipse;
            paintCanvas.Cursor = Cursors.Cross;
            
        }

        private void btnRectangle_Click(object sender, RoutedEventArgs e)
        {
            doc.drawType = DrawType.rectangle;
            paintCanvas.Cursor = Cursors.Cross;
        }

        private void btnBucket_Click(object sender, RoutedEventArgs e)
        {
            doc.drawType = DrawType.fill;
            paintCanvas.Cursor = Cursors.Pen;
        }

        private void btnErazer_Click(object sender, RoutedEventArgs e)
        {
            doc.drawType = DrawType.erase;
            paintCanvas.Cursor = Cursors.Arrow;
        }

        private void btnText_Click(object sender, RoutedEventArgs e)
        {
            doc.drawType = DrawType.text;
            paintCanvas.Cursor = Cursors.IBeam;
        }

        private void btnTriangle_Click(object sender, RoutedEventArgs e)
        {
            doc.drawType = DrawType.triangle;
            paintCanvas.Cursor = Cursors.Cross;
        }

        private void btnArrow_Click(object sender, RoutedEventArgs e)
        {
            doc.drawType = DrawType.arrow;
            paintCanvas.Cursor = Cursors.Cross;
        }

        private void btnHeart_Click(object sender, RoutedEventArgs e)
        {
            doc.drawType = DrawType.heart;
            paintCanvas.Cursor = Cursors.Cross;
        }

        private void paintCanvas_MouseDown(object sender, MouseButtonEventArgs e)
        {
            
            mDown = e.GetPosition(this.paintCanvas);
            capture = true;
            if (doc.drawType == DrawType.brush || doc.drawType == DrawType.pencil || doc.drawType == DrawType.erase)
            {           
                pathGeometry = new PathGeometry();              
                pathFigure = new PathFigure();
                pathFigure.StartPoint = mDown;
                pathFigure.IsClosed = false;
                pathGeometry.Figures.Add(pathFigure);
                path = new Path();
                path.Stroke = new SolidColorBrush(penColor);
                if (doc.drawType == DrawType.erase)
                {
                    path.Stroke = new SolidColorBrush(Colors.White);
                }
                if (doc.drawType == DrawType.brush || doc.drawType == DrawType.erase)
                {
                    path.StrokeThickness = penThickness;
                }
                else if(doc.drawType == DrawType.pencil)
                {
                    path.StrokeThickness = 1;
                }
                path.Data = pathGeometry;
                doc.DrawShape(path, 1);
            }

            if (doc.drawType == DrawType.text)  //Insert text
            {
                TextBox txt = new TextBox();
                txt.Width = 100;
                txt.Height = 20;
                txt.FontFamily = fontFamily;
                txt.FontSize = fontSize;
                txt.FontStyle = fontStyle;
                txt.FontWeight = fontWeight;
                if (decoration != null)
                {
                    txt.TextDecorations = decoration;
                }
                txt.LostKeyboardFocus += txt_LostKeyboardFocus;
                txt.SizeChanged += txt_SizeChanged;
                txt.TextChanged += txt_TextChanged;
                txt.GotKeyboardFocus += txt_GotKeyboardFocus;
                txt.TextWrapping = TextWrapping.Wrap;
                txt.HorizontalAlignment = System.Windows.HorizontalAlignment.Center;
                ContentControl control = new ContentControl();
                Canvas.SetLeft(control, mDown.X);
                Canvas.SetTop(control, mDown.Y);
                control.Content = txt;
                control.Width = 100;
                control.Height = 20;
                //control.Padding = new Thickness(1);
                control.Background = new SolidColorBrush(Colors.White);
                control.Style = FindResource("DesignerItemStyle") as Style;
                doc.InsertText(control);
            }
           
        }

        private void txt_GotKeyboardFocus(object sender, KeyboardFocusChangedEventArgs e)
        {
            TextBox txt = (TextBox)sender;
            oldLineCount = txt.LineCount;

        }

        void txt_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox txt = (TextBox)sender;
      
            if (txt.LineCount > oldLineCount)
            {
               
                ((ContentControl)txt.Parent).Height += txt.FontSize;
                txt.Height += txt.FontSize;
                oldLineCount = txt.LineCount;
                
            }
        }

        void txt_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            //TextBox txt = (TextBox)sender;
            //((ContentControl)txt.Parent).Width = txt.Width;
            //((ContentControl)txt.Parent).Height = txt.Height;
        }
       

        void txt_LostKeyboardFocus(object sender, KeyboardFocusChangedEventArgs e)
        {
            focusedTextbox = (TextBox)sender;
        }

       

        private void paintCanvas_MouseMove(object sender, MouseEventArgs e)
        {
            mMove = e.GetPosition(this.paintCanvas);
            bool addShape = false;
            if ((doc.drawType == DrawType.ellipse || doc.drawType == DrawType.rectangle || doc.drawType == DrawType.triangle || doc.drawType == DrawType.arrow || doc.drawType == DrawType.heart) && capture)
            {
                
                if(curShape == null)
                {
                    
                    if (doc.drawType == DrawType.ellipse)
                    {
                        curShape = new Ellipse();
                    }
                    else if(doc.drawType == DrawType.rectangle)
                    {
                        curShape = new Rectangle();
                    }
                    else if (doc.drawType == DrawType.triangle)
                    {
                        
                        curShape = new Triangle();
                        ((Triangle)curShape).Start = mDown;
                    }
                    else if (doc.drawType == DrawType.arrow)
                    {

                        curShape = new Arrow();
                        ((Arrow)curShape).Start = mDown;
                    }
                    else
                    {
                        curShape = new Heart();
                        ((Heart)curShape).Start = mDown;
                    }
                    addShape = true;
                    curShape.StrokeThickness = penThickness;
                    curShape.Stroke = new SolidColorBrush(penColor);
                }
              
                if (mMove.X <= mDown.X && mMove.Y <= mDown.Y)  //Góc phần tư thứ nhất
                {
                    curShape.Margin = new Thickness(mMove.X, mMove.Y, 0, 0);
                }
                else if (mMove.X >= mDown.X && mMove.Y <= mDown.Y)
                {
                    curShape.Margin = new Thickness(mDown.X, mMove.Y, 0, 0);
                }
                else if (mMove.X >= mDown.X && mMove.Y >= mDown.Y)
                {
                    curShape.Margin = new Thickness(mDown.X, mDown.Y, 0, 0);
                }
                else if (mMove.X <= mDown.X && mMove.Y >= mDown.Y)
                {
                    curShape.Margin = new Thickness(mMove.X, mDown.Y, 0, 0);
                }
                
                curShape.Width = Math.Abs(mMove.X - mDown.X);
                curShape.Height = Math.Abs(mMove.Y - mDown.Y);
              
               
                if (addShape)
                {
                    doc.DrawCapture(curShape);
                }
            }
            else if (doc.drawType == DrawType.line && capture)
            {
                if (curLine == null)
                {
                    curLine = new Line();
                    addShape = true;
                }
                curLine.X1 = mDown.X;
                curLine.Y1 = mDown.Y;
                curLine.X2 = mMove.X;
                curLine.Y2 = mMove.Y;
                curLine.StrokeThickness = penThickness;
                curLine.Stroke = new SolidColorBrush(penColor);
                if (addShape)
                {
                    doc.DrawCapture(curLine);

                }
            }
            else if ((doc.drawType == DrawType.brush || doc.drawType == DrawType.pencil || doc.drawType == DrawType.erase) && capture)
            {
                LineSegment ls = new LineSegment();
                ls.Point = mMove;
                pathFigure.Segments.Add(ls);
            }
        }

        private void paintCanvas_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            capture = false;
            if (curShape != null)
            {
                if (doc.drawType == DrawType.ellipse || doc.drawType == DrawType.rectangle || doc.drawType == DrawType.triangle || doc.drawType == DrawType.arrow || doc.drawType == DrawType.heart)
                {
                    Shape temp;
                    if (doc.drawType == DrawType.ellipse)
                    {
                        temp = new Ellipse();
                    }
                    else if(doc.drawType == DrawType.rectangle)
                    {
                        temp = new Rectangle();
                    }
                    else if (doc.drawType == DrawType.triangle)
                    {
                        temp = new Triangle();
                    }
                    else if (doc.drawType == DrawType.arrow)
                    {
                        temp = new Arrow();
                    }
                    else
                    {
                        temp = new Heart();
                    }
                    temp.Stroke = new SolidColorBrush(penColor);
                    temp.StrokeThickness = penThickness;
                    curControl = new ContentControl();
                    temp.IsHitTestVisible = true;
                    if (doc.drawType == DrawType.triangle)
                    {
                        ((Triangle)temp).Start = ((Triangle)curShape).Start;
                        temp.Width = curShape.Width;
                        temp.Height = curShape.Height;
                    }
                    if (doc.drawType == DrawType.arrow)
                    {
                        ((Arrow)temp).Start = ((Arrow)curShape).Start;
                        temp.Width = curShape.Width;
                        temp.Height = curShape.Height;
                    }
                    if (doc.drawType == DrawType.heart)
                    {
                        ((Heart)temp).Start = ((Heart)curShape).Start;
                        temp.Width = curShape.Width;
                        temp.Height = curShape.Height;
                    }
                    Canvas.SetLeft(curControl, curShape.Margin.Left);
                    Canvas.SetTop(curControl, curShape.Margin.Top);
                    curControl.Width = curShape.Width;
                    curControl.Height = curShape.Height;
                    curControl.Content = temp;
                    curControl.Style = FindResource("DesignerItemStyle") as Style;
                    curControl.Background = new SolidColorBrush(Colors.White);
                    doc.DrawShape(curControl, GetOutline());

                }

                curShape = null;
            }
            else if (doc.drawType == DrawType.line && curLine != null)
            {
                Line line = new Line();
                line.Stroke = new SolidColorBrush(penColor);
                line.StrokeThickness = penThickness;
                line.X1 = curLine.X1;
                line.X2 = curLine.X2;
                line.Y1 = curLine.Y1;
                line.Y2 = curLine.Y2;
                doc.DrawShape(line, GetOutline());
                curLine = null;
            }

        }

        private void cbxThickness_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

            if (cbxThickness.SelectedIndex == 0)
            {
                penThickness = 1;
            }
            else if (cbxThickness.SelectedIndex == 1)
            {
                penThickness = 3;
            }
            else if (cbxThickness.SelectedIndex == 2)
            {
                penThickness = 5;
            }
            else if (cbxThickness.SelectedIndex == 3)
            {
                penThickness = 7;
            }
            if (paintCanvas.Children.Count > 1)
            {
                if (Selector.GetIsSelected(paintCanvas.Children[1]))
                {
                    selectedControl = paintCanvas.Children[1] as ContentControl;
                    ((Shape)selectedControl.Content).StrokeThickness = penThickness;
                }
                
            }
        }

        private void ColorButton_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Controls.Button btnColor = (System.Windows.Controls.Button)sender;
            Color color = ((SolidColorBrush)btnColor.Background).Color;
            btnColor1.Background = new SolidColorBrush(color);
            penColor = color;
            fillColor = color;
            if (paintCanvas.Children.Count > 1)
            {
                if (Selector.GetIsSelected(paintCanvas.Children[1]))
                {
                    selectedControl = paintCanvas.Children[1] as ContentControl;
                    ((Shape)selectedControl.Content).Stroke = new SolidColorBrush(penColor);
                }

            }
        }

        private void btnOtherColors_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Forms.ColorDialog dlg = new System.Windows.Forms.ColorDialog();
            dlg.AllowFullOpen = true;
            dlg.ShowDialog();
            Color color = new Color();
            color.A = dlg.Color.A;
            color.R = dlg.Color.R;
            color.G = dlg.Color.G;
            color.B = dlg.Color.B;
            btnColor1.Background = new SolidColorBrush(color);
            penColor = color;
            fillColor = color;
            if (paintCanvas.Children.Count > 1)
            {
                if (Selector.GetIsSelected(paintCanvas.Children[1]))
                {
                    selectedControl = paintCanvas.Children[1] as ContentControl;
                    ((Shape)selectedControl.Content).Stroke = new SolidColorBrush(penColor);
                }

            }
        }

        private void menuEdit_Click(object sender, RoutedEventArgs e)
        {
            MenuItem menuItem = e.OriginalSource as MenuItem;
            switch (menuItem.Name)
            {
                case "itemClear":
                    doc.canvas.Children.Clear();
                    break;
                case "itemEditBG":                    
                    System.Windows.Forms.ColorDialog dlg = new System.Windows.Forms.ColorDialog();
                    dlg.AllowFullOpen = true;
                    dlg.ShowDialog();
                    Color color = new Color();
                    color.A = dlg.Color.A;
                    color.R = dlg.Color.R;
                    color.G = dlg.Color.G;
                    color.B = dlg.Color.B;
                    SolidColorBrush bgBrush = new SolidColorBrush(color);
                    doc.canvas.Background = bgBrush;
                    break;
            }
        }

        private void menuFileOpen_Click(object sender, RoutedEventArgs e)
        {
            currentFilePath = doc.OpenFile();
        }
        private void menuFileSave_Click(object sender, RoutedEventArgs e)
        {
            doc.SaveFile(currentFilePath);
        }
        private void menuFileSaveAs_Click(object sender, RoutedEventArgs e)
        {
            doc.SaveFile(currentFilePath);   //Hien thi hop thoai luu tap tin
        }

        private int GetOutline()
        {
            if (btnSmooth.IsChecked == true)
            {
                return 1;
            }
            else if (btnDash.IsChecked == true)
            {
                return 2;
            }
            return 3;
        }

        private void btnSmooth_Checked(object sender, RoutedEventArgs e)
        {
            btnDash.IsChecked = false;
            btnDot.IsChecked = false;
            if (paintCanvas.Children.Count > 1)
            {
                if (Selector.GetIsSelected(paintCanvas.Children[1]))
                {
                    selectedControl = paintCanvas.Children[1] as ContentControl;
                    ((Shape)selectedControl.Content).StrokeDashArray = null;
                }

            }
        }

        private void btnDash_Checked(object sender, RoutedEventArgs e)
        {
            btnSmooth.IsChecked = false;
            btnDot.IsChecked = false;
            double[] dashes = { 4, 4 };
            if (paintCanvas.Children.Count > 1)
            {
                if (Selector.GetIsSelected(paintCanvas.Children[1]))
                {
                    selectedControl = paintCanvas.Children[1] as ContentControl;
                    ((Shape)selectedControl.Content).StrokeDashArray = new DoubleCollection(dashes);
                }

            }
        }

        private void btnDot_Checked(object sender, RoutedEventArgs e)
        {
            btnSmooth.IsChecked = false;
            btnDash.IsChecked = false;
            double[] dashes = { 4, 1, 4, 1 };
            if (paintCanvas.Children.Count > 1)
            {
                if (Selector.GetIsSelected(paintCanvas.Children[1]))
                {
                    selectedControl = paintCanvas.Children[1] as ContentControl;
                    ((Shape)selectedControl.Content).StrokeDashArray = new DoubleCollection(dashes);
                }

            }
        }

        private void paintCanvas_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)  //Select to move/resize/rotate
        {
            if (doc.drawType == DrawType.nothing)
            {
                if (e.Source != paintCanvas && e.Source.GetType() == typeof(ContentControl))
                {
                    Selector.SetIsSelected((ContentControl)e.Source, true);
                }
            }
        }
          


        private void paintCanvas_PreviewMouseLeftButtonUp(object sender, MouseButtonEventArgs e)    //Unselect
        {
            Line temp = new Line();
            if (doc.drawType == DrawType.nothing)
            {
                if (e.Source == paintCanvas && e.Source.GetType() != temp.GetType())
                {
                    foreach (UIElement control in paintCanvas.Children)
                    {
                       
                            Selector.SetIsSelected(control, false);
                      
                    }
                }
            }
            else if (doc.drawType == DrawType.fill)
            {
                System.Drawing.Color color = new System.Drawing.Color();
                color = System.Drawing.Color.FromArgb(fillColor.A, fillColor.R, fillColor.G, fillColor.B);
                System.Drawing.Bitmap bm = doc.CanvasToBitmap(doc.canvas);
                doc.FloodFill(bm, new System.Drawing.Point((int)e.GetPosition(doc.canvas).X, (int)e.GetPosition(doc.canvas).Y), color);
            }
        }

     
        private void My_Paint_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void Copy_Click(object sender, RoutedEventArgs e)
        {
            if (Selector.GetIsSelected(paintCanvas.Children[paintCanvas.Children.Count - 1]))
            {
                selectedControl = paintCanvas.Children[paintCanvas.Children.Count - 1] as ContentControl;
            }
        }

        private void Cut_Click(object sender, RoutedEventArgs e)
        {
            bool needCut = false;
            if (Selector.GetIsSelected(paintCanvas.Children[paintCanvas.Children.Count - 1]))
            {
                selectedControl = paintCanvas.Children[paintCanvas.Children.Count - 1] as ContentControl;
                needCut = true;
            }
            if (needCut == true)
            {
                doc.canvas.Children.Remove(selectedControl);
            }
        }

        private void Paste_Click(object sender, RoutedEventArgs e)
        {
            if (selectedControl != null)
            {
                if(doc.canvas.Children.Contains(selectedControl))   //Neu da ton tai, tao them nhan ban
                {
                    ContentControl temp = new ContentControl();
                    temp.Width = selectedControl.Width;
                    temp.Height = selectedControl.Height;
                    temp.Style = FindResource("DesignerItemStyle") as Style;
                    Shape tempShape;
                    if (selectedControl.Content.GetType() == typeof(Ellipse))
                    {
                        tempShape = new Ellipse();
                    }
                    else
                    {
                        tempShape = new Rectangle();
                    }
                    tempShape.Stroke = ((Shape)selectedControl.Content).Stroke;
                    tempShape.StrokeThickness = ((Shape)selectedControl.Content).StrokeThickness;
                    tempShape.Fill = ((Shape)selectedControl.Content).Fill;
                    tempShape.IsHitTestVisible = false;
                    temp.Content = tempShape;
                    Canvas.SetLeft(temp, 0);
                    Canvas.SetTop(temp, 0);
                    selectedControl = temp;
                }
                
                doc.canvas.Children.Add(selectedControl);
            }
        }

        private void paintCanvas_ContextMenuOpening(object sender, ContextMenuEventArgs e)
        {
           //var result = VisualTreeHelper.HitTest(paintCanvas, new Point(e.CursorLeft, e.CursorTop));
           //if (result != null)
           //{
           //     selectedControl = result.VisualHit as ContentControl;              
           //}
        }

        private void btnOtherColorsText_Click(object sender, RoutedEventArgs e)
        {

            System.Windows.Forms.ColorDialog dlg = new System.Windows.Forms.ColorDialog();
            dlg.AllowFullOpen = true;
            dlg.ShowDialog();
            Color color = new Color();
            color.A = dlg.Color.A;
            color.R = dlg.Color.R;
            color.G = dlg.Color.G;
            color.B = dlg.Color.B;           
            btnColorText.Background = new SolidColorBrush(color);
            if (focusedTextbox != null)
            {
                focusedTextbox.Foreground = btnColorText.Background;
            }
        }

        private void cbxFontFamily_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            
            fontFamily = new FontFamily(cbxFontFamily.Items[cbxFontFamily.SelectedIndex].ToString());
            if (focusedTextbox != null)
            {
                focusedTextbox.FontFamily = fontFamily;
            }
        }

        private void cbxFontSize_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (cbxFontSize.SelectionBoxItem != null)
            {
                ComboBoxItem ComboItem = (ComboBoxItem)cbxFontSize.SelectedItem;
                string value = ComboItem.Content.ToString();
                fontSize = Convert.ToDouble(value);
                if (focusedTextbox != null)
                {
                    focusedTextbox.FontSize = fontSize;
                }
            }
        }

        private void btnBold_Click(object sender, RoutedEventArgs e)
        {       
            bold = !bold;
            if (bold)
            {
                if (focusedTextbox != null)
                {
                    focusedTextbox.FontWeight = FontWeights.Bold;
                }
            }
            else
            {
                if (focusedTextbox != null)
                {
                    focusedTextbox.FontWeight = FontWeights.Normal;
                }
            }
        }

        private void btnItalic_Click(object sender, RoutedEventArgs e)
        {
            italic = !italic;
            if (italic)
            {
                if (focusedTextbox != null)
                {
                    focusedTextbox.FontStyle = FontStyles.Italic;
                }
            }
            else
            {
                if (focusedTextbox != null)
                {
                    focusedTextbox.FontStyle = FontStyles.Normal;
                }
            }
        }

        private void btnUnderlined_Click(object sender, RoutedEventArgs e)
        {
            underlined = !underlined;
            if (underlined)
            {
                if (focusedTextbox != null)
                {
                    if (focusedTextbox.TextDecorations == null)
                    {
                        focusedTextbox.TextDecorations = new TextDecorationCollection();
                    }
                    focusedTextbox.TextDecorations = TextDecorations.Underline;

                }
            }
            else
            {
                if (focusedTextbox != null)
                {
                    focusedTextbox.TextDecorations = null;
                }
            }
        }

        private void ColorTextButton_Click(object sender, RoutedEventArgs e)
        {
            btnColorText.Background = ((Button)sender).Background;
            if (focusedTextbox != null)
            {
                focusedTextbox.Foreground = btnColorText.Background;
            }
        }

        private void CanvasSizeChange(object sender, KeyboardFocusChangedEventArgs e)   //Change size of canvas
        {
            UpdateCanvasSize();
        }

        private void UpdateCanvasSize()
        {
            if (txtWidth.Text == "")
            {
                txtWidth.Text = doc.canvas.Width.ToString();
            }
            if (txtHeight.Text == "")
            {
                txtHeight.Text = doc.canvas.Height.ToString();
            }
            try
            {
                if (txtWidth.Text != "" && txtHeight.Text != "")
                {
                    doc.canvas.ClipToBounds = true;
                    doc.canvas.SnapsToDevicePixels = true;
                    doc.canvas.Width = Convert.ToDouble(txtWidth.Text);
                    doc.canvas.Height = Convert.ToDouble(txtHeight.Text);
                }
            }
            catch (FormatException ex)
            {
                MessageBox.Show("Invalid size of paint surface: " + "\n" + ex.Message, "Invalid input", MessageBoxButton.OK, MessageBoxImage.Error);
            }
            
        }

        private void ConfirmCanvasSize(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Return)
            {
                UpdateCanvasSize();
            }
            else
            {
                System.Windows.Input.Key k = e.Key;
                if (Key.D0 <= k && k <= Key.D9 ||
                    Key.NumPad0 <= k && k <= Key.NumPad9 ||
                    k == Key.OemMinus || k == Key.Subtract ||
                    k == Key.Decimal || k == Key.OemPeriod)
                {
                }
                else
                {
                    e.Handled = true;

                    // just a little sound effect for wrong key pressed
                    System.Media.SystemSound ss = System.Media.SystemSounds.Beep;
                    ss.Play();

                }
            }
        }

        private void paintCanvas_KeyDown(object sender, KeyEventArgs e) 
        {
            if (e.Key == Key.Delete) //Delete a shape
            {
                if (selectedControl != null)
                {
                    doc.RemoveShape(selectedControl);
                }
            }
        }

        private void paintCanvas_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Delete) //Delete a shape
            {
                if (selectedControl != null)
                {
                    doc.RemoveShape(selectedControl);
                }
            }
        }

        private void My_Paint_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Delete) //Delete a shape
            {
                if(Selector.GetIsSelected(paintCanvas.Children[paintCanvas.Children.Count - 1]))
                {
                    selectedControl = paintCanvas.Children[paintCanvas.Children.Count - 1] as ContentControl;
                }
                if (selectedControl != null)
                {
                    doc.RemoveShape(selectedControl);
                }
            }
        }

       

        
    }
}
