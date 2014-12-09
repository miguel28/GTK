VERSION 5.00
Begin VB.Form NewFileWindow 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Nuevo Archivo..."
   ClientHeight    =   4470
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   6960
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   ScaleHeight     =   4470
   ScaleWidth      =   6960
   ShowInTaskbar   =   0   'False
   Begin VB.Frame Frame5 
      Caption         =   "Corte"
      Height          =   1455
      Left            =   2640
      TabIndex        =   16
      Top             =   2280
      Width           =   1815
      Begin VB.OptionButton Option8 
         Caption         =   "Fuera"
         Height          =   255
         Left            =   240
         TabIndex        =   19
         Top             =   1080
         Width           =   1095
      End
      Begin VB.OptionButton Option7 
         Caption         =   "Dentro"
         Height          =   375
         Left            =   240
         TabIndex        =   18
         Top             =   600
         Width           =   1215
      End
      Begin VB.OptionButton Option6 
         Caption         =   "Medio"
         Height          =   375
         Left            =   240
         TabIndex        =   17
         Top             =   240
         Value           =   -1  'True
         Width           =   1215
      End
   End
   Begin VB.Frame Frame4 
      Caption         =   "Velocidad Del Husillo"
      Height          =   855
      Left            =   360
      TabIndex        =   14
      Top             =   2280
      Width           =   2055
      Begin VB.TextBox Text3 
         Height          =   285
         Left            =   360
         TabIndex        =   15
         Text            =   "2000"
         Top             =   360
         Width           =   1215
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "Tamaño"
      Height          =   1335
      Left            =   360
      TabIndex        =   9
      Top             =   360
      Width           =   2055
      Begin VB.TextBox Text2 
         Height          =   285
         Left            =   960
         TabIndex        =   11
         Text            =   "50"
         Top             =   720
         Width           =   855
      End
      Begin VB.TextBox Text1 
         Height          =   285
         Left            =   960
         TabIndex        =   10
         Text            =   "80"
         Top             =   240
         Width           =   855
      End
      Begin VB.Label Label2 
         Caption         =   "Alto"
         Height          =   255
         Left            =   240
         TabIndex        =   13
         Top             =   720
         Width           =   495
      End
      Begin VB.Label Label1 
         Caption         =   "Ancho"
         Height          =   255
         Left            =   240
         TabIndex        =   12
         Top             =   360
         Width           =   615
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Sistema de Unidades"
      Height          =   1335
      Left            =   4800
      TabIndex        =   3
      Top             =   360
      Width           =   1815
      Begin VB.OptionButton Option5 
         Caption         =   "Pulgadas"
         Height          =   255
         Left            =   360
         TabIndex        =   8
         Top             =   840
         Width           =   1335
      End
      Begin VB.OptionButton Option4 
         Caption         =   "Milimetros"
         Height          =   255
         Left            =   360
         TabIndex        =   7
         Top             =   360
         Value           =   -1  'True
         Width           =   1335
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Plano de Corte"
      Height          =   1695
      Left            =   2760
      TabIndex        =   2
      Top             =   360
      Width           =   1695
      Begin VB.OptionButton Option3 
         Caption         =   "Plano YZ"
         Height          =   255
         Left            =   120
         TabIndex        =   6
         Top             =   1200
         Width           =   1095
      End
      Begin VB.OptionButton Option2 
         Caption         =   "Plano XZ"
         Height          =   375
         Left            =   120
         TabIndex        =   5
         Top             =   720
         Width           =   975
      End
      Begin VB.OptionButton Option1 
         Caption         =   "Plano XY"
         Height          =   375
         Left            =   120
         TabIndex        =   4
         Top             =   360
         Value           =   -1  'True
         Width           =   1095
      End
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancelar"
      Height          =   375
      Left            =   3600
      TabIndex        =   1
      Top             =   3960
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "Crear"
      Height          =   375
      Left            =   1800
      TabIndex        =   0
      Top             =   3960
      Width           =   1215
   End
End
Attribute VB_Name = "NewFileWindow"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub CancelButton_Click()
Me.Hide
End Sub

Private Sub Label6_Click()

End Sub

Private Sub OKButton_Click()
StartProgram = ""
If Option1.Value = True Then
    StartProgram = "G17 "
ElseIf Option2.Value = True Then
    StartProgram = "G18 "
ElseIf Option3.Value = True Then
    StartProgram = "G19 "
End If

StartProgram = StartProgram & "G90 G54 "

If Option4.Value = True Then
    StartProgram = StartProgram & "M71" & vbCrLf
ElseIf Option5.Value = True Then
    StartProgram = StartProgram & "M72" & vbCrLf
End If

StartProgram = StartProgram & "T05 M06" & vbCrLf & "S" & Text3.Text & " M05" & vbCrLf

If Option6.Value = True Then
    StartProgram = StartProgram & "G40 G43 "
ElseIf Option7.Value = True Then
    StartProgram = StartProgram & "G41 G43 "
ElseIf Option8.Value = True Then
    StartProgram = StartProgram & "G42 G43 "
End If

StartProgram = StartProgram & vbCrLf & "G00 X0 Y0 Z1 F100"

PartWidth = Val(Text1.Text)
PartHeight = Val(Text2.Text)

EndProgram = "M30" & vbCrLf & "G28"

Desing.Show
Me.Hide

End Sub

