#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "../webserv.hpp"

class Location
{
	private:
		
		std::string						_prefix; // location /{}  or location /gallery {}
		std::set<std::string>			_allowedMethods;
		std::string						_indexPage;
		bool							_isRedirected;


		std::pair<int, std::string>		_redirection; /* is a way to forward visitors and search engines from one URL to another.
														Redirects are used when moving content to a new URL,
														when deleting pages or when changing domain names or merging websites*/
		

	public:
		Location();
		Location( Location const & src );
		~Location();

		Location &		operator = ( Location const & rhs );

		// Setters
		
		void			setPrefix(std::string prefix);
		void			addAllowedMethod(std::string method);
		void			setIndexPage(std::string indexPagePath);
		void			setRedirection(int code, std::string url);

		// Accessors

		std::string						getPrefix() const;
		std::string						getIndexPage() const;
		std::set<std::string> & 		getAllowedMethods();
		//std::string						getRoot() const {return "www";}; /* temporait pour compille*/
		bool							isRedirected() const;
		std::pair<int, std::string>		getRedirection() const;
		
		// Methods
		
		bool			isAllowedMethod(std::string method) const;
		

};

#endif 
