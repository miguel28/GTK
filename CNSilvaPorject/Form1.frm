VERSION 5.00
Begin VB.Form Desing 
   Caption         =   "Form1"
   ClientHeight    =   11250
   ClientLeft      =   120
   ClientTop       =   450
   ClientWidth     =   14055
   DrawWidth       =   4
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   11250
   ScaleWidth      =   14055
   Begin VB.Frame Frame1 
      Caption         =   "Bloquear"
      Height          =   1695
      Left            =   4080
      TabIndex        =   13
      Top             =   8520
      Width           =   1575
      Begin VB.OptionButton Option3 
         Caption         =   "Eje Y"
         Height          =   255
         Left            =   120
         TabIndex        =   16
         Top             =   1320
         Width           =   1335
      End
      Begin VB.OptionButton Option2 
         Caption         =   "Eje X"
         Height          =   255
         Left            =   120
         TabIndex        =   15
         Top             =   840
         Width           =   975
      End
      Begin VB.OptionButton Option1 
         Caption         =   "Ningun Eje"
         Height          =   255
         Left            =   120
         TabIndex        =   14
         Top             =   360
         Value           =   -1  'True
         Width           =   1215
      End
   End
   Begin VB.TextBox Text4 
      Height          =   285
      Left            =   1200
      TabIndex        =   10
      Text            =   "3"
      Top             =   8160
      Width           =   855
   End
   Begin VB.TextBox Text3 
      ForeColor       =   &H00000000&
      Height          =   1095
      Left            =   4680
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   6
      Top             =   6840
      Width           =   6255
   End
   Begin VB.TextBox Text2 
      Height          =   2895
      Left            =   4680
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   5
      Top             =   3240
      Width           =   6255
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Usar Ultimo Punto"
      Height          =   375
      Left            =   2520
      TabIndex        =   4
      Top             =   7560
      Width           =   1575
   End
   Begin VB.TextBox Text1 
      Height          =   1695
      Left            =   4800
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   3
      Top             =   600
      Width           =   6135
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Borrar Todo"
      Height          =   375
      Left            =   1200
      TabIndex        =   2
      Top             =   7560
      Width           =   1095
   End
   Begin VB.PictureBox Picture1 
      DrawWidth       =   2
      Height          =   2160
      Left            =   240
      ScaleHeight     =   2100
      ScaleWidth      =   2955
      TabIndex        =   1
      Top             =   240
      Width           =   3015
   End
   Begin VB.Label Label6 
      Caption         =   "Especifique primer punto"
      Height          =   255
      Left            =   2280
      TabIndex        =   12
      Top             =   8160
      Width           =   2175
   End
   Begin VB.Label Label5 
      Caption         =   "Perforacion"
      Height          =   255
      Left            =   120
      TabIndex        =   11
      Top             =   8160
      Width           =   975
   End
   Begin VB.Label Label4 
      Caption         =   "Final del Programa"
      Height          =   255
      Left            =   4680
      TabIndex        =   9
      Top             =   6360
      Width           =   1335
   End
   Begin VB.Label Label3 
      Caption         =   "Cuerpo del Programa"
      Height          =   255
      Left            =   4800
      TabIndex        =   8
      Top             =   2520
      Width           =   1695
   End
   Begin VB.Label Label2 
      Caption         =   "Inicio del Programa"
      Height          =   255
      Left            =   5040
      TabIndex        =   7
      Top             =   120
      Width           =   1455
   End
   Begin VB.Label Label1 
      Caption         =   "Label1"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   7560
      Width           =   735
   End
End
Attribute VB_Name = "Desing"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public mouse_x As Integer
Public mouse_y As Integer
Public mouse_x1, mouse_y1 As Integer
Public x1, x2, y1, y2 As Integer
Public x3, x4, y3, y4 As Integer
Public lastX, lastY, lastTX, lastTY As Integer
Dim pclick As Boolean
Dim Drawed As Boolean
Dim FristClick As Boolean
Const OffsetPiece = 5

Private Sub Command1_Click()
    Clear_All
End Sub

Private Sub Command2_Click()
    x1 = lastX
    y1 = lastY
    x3 = lastTX
    y3 = lastTY
            
    pclick = True
    Label6.Caption = "Especifique segundo punto"
    Picture1.Circle (x3, y3), 2
End Sub

Private Sub Form_Load()
    Desing.Caption = Name
    Me.ScaleMode = vbPixels
    Picture1.ScaleMode = vbPixels
    Clear_All
    Picture1.Height = ((PartHeight + (OffsetPiece * 2)) * Zoom)
    Picture1.Width = ((PartWidth + (OffsetPiece * 2)) * Zoom)
    
    Label2.Top = 15
    Label2.Left = Picture1.Width + 35
    
    Text1.Top = 30
    Text1.Left = Picture1.Width + 35
    
    Label3.Top = 150
    Label3.Left = Picture1.Width + 35
    
    Text2.Top = 170
    Text2.Left = Picture1.Width + 35
    
    Label4.Top = 370
    Label4.Left = Picture1.Width + 35
    
    Text3.Top = 390
    Text3.Left = Picture1.Width + 35
    
    Label1.Top = Picture1.Height + 50
    Label1.Left = 50
    
    Command1.Top = Picture1.Height + 50
    Command1.Left = 100
    
    Command2.Top = Picture1.Height + 50
    Command2.Left = 200

    Label5.Top = Picture1.Height + 80
    Label5.Left = 50

    Text4.Top = Picture1.Height + 80
    Text4.Left = 150
    
    Label6.Top = Picture1.Height + 80
    Label6.Left = 220
    
    Frame1.Top = Picture1.Height + 80
    Frame1.Left = 360
    
    Call Clear_All
    
End Sub

Private Sub Picture1_Click()

    If pclick = False Then
            x1 = mouse_x1
            y1 = mouse_y1
            x3 = mouse_x
            y3 = mouse_y
            
            pclick = True
            Label6.Caption = "Especifique segundo punto"
            Picture1.Circle (x3, y3), 2

        Else
        
            If Option2.Value = False Then
                x2 = mouse_x1
                x4 = mouse_x
            ElseIf Option2.Value = True Then
                x2 = x1
                x4 = x3
            End If
            
            If Option3.Value = False Then
                y2 = mouse_y1
                y4 = mouse_y
            ElseIf Option3.Value = True Then
                y2 = y1
                y4 = y3
            End If
            
            lastX = x2
            lastY = y2
            lastTX = x4
            lastTY = y4
            Label6.Caption = "Especifique primer punto"
            Picture1.Line (x3, y3)-(x4, y4), vbBlue

            Picture1.Circle (x4, y4), 3
            
            Dim TX1, TX2, TY1, TY2 As String
            TX1 = x1
            TX2 = x2
            TY1 = y1
            TY2 = y2
            
            Program = Program & "G00 X" & TX1 & " Y" & TY1 & " Z0  F100" & vbCrLf _
                    & "G01 Z-" & Text4.Text & vbCrLf _
                    & "G01 X" & TX2 & " Y" & TY2 & " Z-" & Text4.Text & vbCrLf _
                    & "G00 Z3" & vbCrLf
            pclick = False
    End If
    Text2.Text = Program
End Sub

Private Sub Picture1_MouseMove(Button As Integer, Shift As Integer, x As Single, Y As Single)
    mouse_x = x
    mouse_y = Y
    
    mouse_x1 = Int(x / Zoom) - OffsetPiece
    mouse_y1 = Int((Y / Zoom) - OffsetPiece - PartHeight) * -1
    
    Label1.Caption = Str(mouse_x1) + Str(mouse_y1)
    
    If Drawed = False Then
    Clear_All
    Drawed = True
    End If
    
End Sub


Private Sub Clear_All()
    Picture1.Cls
    Program = ""
    
    'Dim i, j As Byte
    'Picture1.DrawWidth = 1
    
    'For i = 0 To PartWidth + (2 * OffsetPiece)
    '    Picture1.Line (i * Zoom, 0)-(i * Zoom, (PartHeight + (2 * OffsetPiece)) * Zoom)
    'Next i
    
    'For i = 0 To PartHeight + (2 * OffsetPiece)
    '    Picture1.Line (0, i * Zoom)-((PartWidth + (2 * OffsetPiece)) * Zoom, i * Zoom)
    'Next i
    
    'Picture1.DrawWidth = 2
    Picture1.Line ((OffsetPiece) * Zoom, OffsetPiece * Zoom)-((OffsetPiece + PartWidth) * Zoom, (OffsetPiece) * Zoom), vbRed
    Picture1.Line ((OffsetPiece + PartWidth) * Zoom, OffsetPiece * Zoom)-((OffsetPiece + PartWidth) * Zoom, (OffsetPiece + PartHeight) * Zoom), vbRed
    Picture1.Line (OffsetPiece * Zoom, OffsetPiece * Zoom)-((OffsetPiece) * Zoom, (OffsetPiece + PartHeight) * Zoom), vbRed
    Picture1.Line ((OffsetPiece) * Zoom, (OffsetPiece + PartHeight) * Zoom)-((OffsetPiece + PartWidth) * Zoom, (OffsetPiece + PartHeight) * Zoom), vbRed
    
    
    Text1.Text = StartProgram
    Text2.Text = Program
    Text3.Text = EndProgram
End Sub

