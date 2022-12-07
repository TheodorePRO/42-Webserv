#ifndef PARSERCONF_HPP
# define PARSERCONF_HPP

# include "../webserv.hpp"

class GlobalConfiguration;
class ServerInParser;
class Location;

class ParserConf
{
	private:
		std::string				_inputFilePath;
		GlobalConfiguration &	_globalConf;

		// used for the parsing
		std::string				_context;
		ServerInParser*			_currentServer;
		Location*				_currentLocation;

		// privet function for parsing
		void	_parseFile();
		void	_parseLine(std::vector<std::string> & line_items, std::size_t line_nb);
		void	_parseServerLine(std::vector<std::string> & line_items, std::size_t line_nb);
		void	_parseLocationLine(std::vector<std::string> & line_items, std::size_t line_nb);
		void	_checkServerDuplicate();
		void	_checkCurrentServerIntegrity(std::size_t line_nb) const;
		void	_checkCurrentLocationIntegrity(std::size_t line_nb) const;
		void	_solveCurrentLocationIntegrity();


	public:
		// parser cannot be constructed without conf file and global conf
		ParserConf(std::string inputFilePath, GlobalConfiguration & globalConf);
		ParserConf( ParserConf const & src );
		~ParserConf();

		ParserConf &	operator=( ParserConf const & rhs );
		/*class parsing_error: public std::exception
		{
			private:
				const char * _msg;
			
			public:
				parsing_error() {}
				parsing_error(const char * msg): _msg(msg) {}
				virtual const char * what () const throw ()
				{
					return _msg;
				}
		};

		class syntax_error: public std::exception
		{
			private:
				const char * _msg;
			public:
				syntax_error() {}
				syntax_error(const char * msg): _msg(msg) {}
				virtual const char * what () const throw ()
				{
					return _msg;
				}
		};*/
};

#endif /* ********************************************* ParserConf_H */
