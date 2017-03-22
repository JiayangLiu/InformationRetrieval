package com.herman.jqm.servlet;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * @see �ж����õ��û��������ն�
 */
public class AgentServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;

    /**
     * Ĭ�Ϲ��췽��
     */
    public AgentServlet() {
    }

	/**
	 * @see doGet����
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doPost(request, response);
	}

	/**
	 * @see doPost
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String header=request.getHeader("user-agent");
		String ct=request.getContentType();
		System.out.println("user-agent:"+header);
		System.out.println("ContentType:"+ct);
		String at=request.getAuthType();
		System.out.println("AuthType:"+at);
		String protocol=request.getProtocol();
		System.out.println("Protocol:"+protocol);
		response.sendRedirect("news/home.html");
	}

}
