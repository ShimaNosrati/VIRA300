' =================================================================================================
'   CComMessageFilter class
'
' Copyright © InnovMetric Software Inc. 2018 All Rights Reserved
' -------------------------------------------------------------------------------------------------

Imports System.Runtime.InteropServices
Imports System.Threading

' Some declarations needed to map to the underlying COM concept of a message filter.
' See MSDN for more information.
<ComImport(), _
Guid("00000016-0000-0000-C000-000000000046"), _
InterfaceTypeAttribute(ComInterfaceType.InterfaceIsIUnknown)> _
Interface IOleMessageFilter
    <PreserveSig()> _
    Function HandleInComingCall(ByVal dwCallType As Integer, _
                                ByVal hTaskCaller As IntPtr, _
                                ByVal dwTickCount As Integer, _
                                ByVal lpInterfaceInfo As IntPtr) _
                                As Integer

    <PreserveSig()> _
    Function RetryRejectedCall(ByVal hTaskCallee As IntPtr, _
                               ByVal dwTickCount As Integer, _
                               ByVal dwRejectType As Integer) _
                               As Integer

    <PreserveSig()> _
    Function MessagePending(ByVal hTaskCallee As IntPtr, _
                            ByVal dwTickCount As Integer, _
                            ByVal dwPendingType As Integer) _
                            As Integer
End Interface

Enum SERVERCALL
    SERVERCALL_ISHANDLED = 0
    SERVERCALL_REJECTED = 1
    SERVERCALL_RETRYLATER = 2
End Enum

Enum PENDINGMSG
    PENDINGMSG_CANCELCALL = 0
    PENDINGMSG_WAITNOPROCESS = 1
    PENDINGMSG_WAITDEFPROCESS = 2
End Enum

' =================================================================================================
' Class implementing a COM message filter. This is needed so that COM calls
' do not throw an exception and instead retry if the main thread is busy.
'
' This is a simplified implementation that does not handle all possible cases but is usually
' sufficient for the needs of a PolyWorks external module.
' -------------------------------------------------------------------------------------------------
Public Class CComMessageFilter
    Implements IOleMessageFilter

    ' =================================================================================================
    ' Constructor. Immediately register this filter.
    ' -------------------------------------------------------------------------------------------------	
    Public Sub New()
        Dim oldFilter As IOleMessageFilter = Nothing
        Dim iRetVal As Integer

        If (Thread.CurrentThread.GetApartmentState() = ApartmentState.STA) Then
            iRetVal = CoRegisterMessageFilter(Me, oldFilter)
        Else
            Throw New COMException("Unable to register message filter because the current thread apartment state is not STA.")
        End If
    End Sub

    ' =================================================================================================
    ' Destructor. Unregister the filter.
    ' -------------------------------------------------------------------------------------------------
    Public Sub Finalize()
        Dim oldFilter As IOleMessageFilter = Nothing
        CoRegisterMessageFilter(Nothing, oldFilter)
    End Sub

    ' =================================================================================================
    ' Implementation of IMessageFilter. See Microsoft documentation.
    ' In our case we accept all calls.
    ' -------------------------------------------------------------------------------------------------
    Private Function HandleInComingCall(ByVal dwCallType As Integer, _
                                        ByVal hTaskCaller As System.IntPtr, _
                                        ByVal dwTickCount As Integer, _
                                        ByVal lpInterfaceInfo As System.IntPtr) _
                                        As Integer Implements IOleMessageFilter.HandleInComingCall

        Return SERVERCALL.SERVERCALL_ISHANDLED
    End Function

    ' =================================================================================================
    ' Implementation of IMessageFilter. See Microsoft documentation.
    ' In our case we always ask for a retry when it is possible.
    ' -------------------------------------------------------------------------------------------------	
    Private Function RetryRejectedCall(ByVal hTaskCallee As System.IntPtr, _
                                       ByVal dwTickCount As Integer, _
                                       ByVal dwRejectType As Integer) _
                                       As Integer Implements IOleMessageFilter.RetryRejectedCall

        If dwRejectType = SERVERCALL.SERVERCALL_RETRYLATER Then
            Return 200
        End If

        Return -1
    End Function

	' =================================================================================================
    ' Implementation of IMessageFilter. See Microsoft documentation.
    ' -------------------------------------------------------------------------------------------------
    Private Function MessagePending(ByVal hTaskCallee As System.IntPtr, _
                                    ByVal dwTickCount As Integer, _
                                    ByVal dwPendingType As Integer) _
                                    As Integer Implements IOleMessageFilter.MessagePending

        Return PENDINGMSG.PENDINGMSG_WAITDEFPROCESS
    End Function

    <DllImport("Ole32.dll")> _
    Private Shared Function CoRegisterMessageFilter(ByVal newFilter As IOleMessageFilter, _
                                                    ByRef oldFilter As IOleMessageFilter) _
                                                    As Integer
    End Function
End Class
