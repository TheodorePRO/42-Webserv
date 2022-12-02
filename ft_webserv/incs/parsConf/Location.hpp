#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "../webserv.hpp"

class Location
{
	private:
		
		std::string						_prefix; // location /{}  or location /gallery {}
		std::string						_root;
		std::set<std::string>			_allowedMethods;
		std::string						_indexPage;
		bool							_autoindex;
		bool							_isRedirected;

		size_t							_maxSize;

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
		void			setRoot(std::string path);
		void			addAllowedMethod(std::string method);
		void			setIndexPage(std::string indexPagePath);
		void			setAutoindex(std::string on_off);
		void			setRedirection(int code, std::string url);

		// Accessors

		std::string						getPrefix() const;
		std::string						getIndexPage() const;
		bool							isAutoindexed() const;
		std::set<std::string> & 		getAllowedMethods();
		std::string						getRoot() const;
		bool							isRedirected() const;
		std::pair<int, std::string>		getRedirection() const;
		size_t							getMaxSize() const;
		
		// Methods
		
		bool			isAllowedMethod(std::string method) const;
		

};

#endif 
